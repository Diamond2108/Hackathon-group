import os
import pandas as pd
import streamlit as st
from serial.tools import list_ports

# ---------- colors ----------
PURPLE = "#8E44AD"
GREEN = "#2ECC71"
PINK = "#FF69B4"

# ---------- page setup ----------
st.set_page_config(page_title="Study Session Tracker", page_icon="📚")

st.markdown(
    f"""
    <style>
    h1, h2, h3 {{ color: {PURPLE}; }}
    [data-testid="stMetric"] {{
        background-color: #F7F0FA;
        border-left: 6px solid {PURPLE};
        padding: 12px;
        border-radius: 10px;
    }}
    [data-testid="stMetricValue"] {{ color: {PURPLE}; }}
    [data-testid="stMetricLabel"], [data-testid="stMetricLabel"] * {{
        color: {PINK};
        font-weight: bold;
    }}
    .stButton > button {{
        background-color: {PINK};
        color: white;
        border: none;
        border-radius: 8px;
    }}
    .stButton > button:hover {{ background-color: {PURPLE}; color: white; }}
    </style>
    """,
    unsafe_allow_html=True,
)

# ---------- helper functions ----------
ARDUINO_VIDS = {0x2341, 0x2A03, 0x1A86, 0x0403}  # Arduino, clones (CH340), FTDI


def find_arduino():
    """Return the serial port of a connected Arduino, or None."""
    for port in list_ports.comports():
        name = (port.description or "").lower()
        if port.vid in ARDUINO_VIDS or "arduino" in name:
            return port
    return None


def get_level(xp):
    """Level thresholds go 50, 100, 150, ... Returns (level, floor, next_threshold)."""
    level = 0
    threshold = 50
    while xp >= threshold:
        level += 1
        threshold += 50
    return level, threshold - 50, threshold


def load_csv(path, column):
    """Read one column of a CSV as numbers. Returns None if the file is missing/empty."""
    if not os.path.exists(path):
        return None
    df = pd.read_csv(path)
    values = pd.to_numeric(df[column], errors="coerce").dropna()
    return values if len(values) > 0 else None


# ---------- sidebar settings ----------
st.sidebar.header("Settings")
light_path = st.sidebar.text_input("Light CSV", "light.csv")
time_path = st.sidebar.text_input("Time CSV", "time.csv")
unit = st.sidebar.selectbox("Units in time.csv", ["Seconds", "Milliseconds", "Minutes"])
divisor = {"Seconds": 60, "Milliseconds": 60000, "Minutes": 1}[unit]

# ---------- title ----------
st.title("📚 Study Session Tracker")

# ---------- arduino status ----------
st.subheader("Arduino status")
arduino = find_arduino()
if arduino:
    st.markdown(
        f"<div style='background:{GREEN};color:white;padding:10px;border-radius:8px;'>"
        f"✅ Arduino connected on <b>{arduino.device}</b></div>",
        unsafe_allow_html=True,
    )
else:
    st.markdown(
        f"<div style='background:{PINK};color:white;padding:10px;border-radius:8px;'>"
        f"❌ No Arduino detected. Plug it in and press Refresh.</div>",
        unsafe_allow_html=True,
    )
st.button("Refresh")  # clicking any button reruns the script

# ---------- load data ----------
times = load_csv(time_path, "value")
lights = load_csv(light_path, "over_threshold")

if times is None or lights is None:
    st.info("Waiting for data. Make sure light.csv and time.csv exist and contain readings.")
    st.stop()

# ---------- calculations ----------
minutes = (times.max() - times.min()) / divisor
light_avg = lights.mean()
well_lit = light_avg > 0.75
xp = minutes * 2
level, floor_xp, next_xp = get_level(xp)
progress = (xp - floor_xp) / (next_xp - floor_xp)

# ---------- session results ----------
st.subheader("Session results")
col1, col2, col3 = st.columns(3)
col1.metric("Session length", f"{minutes:.1f} min")
col2.metric("Average light", f"{light_avg:.2f}")
col3.metric("XP earned", f"{xp:.0f}")

if well_lit:
    st.markdown(
        f"<h3 style='color:{GREEN};'>💡 Well lit environment</h3>", unsafe_allow_html=True
    )
else:
    st.markdown(
        f"<h3 style='color:{PINK};'>🌙 Not a well lit environment</h3>", unsafe_allow_html=True
    )

# ---------- level and progress bar ----------
st.subheader(f"Level {level}")
st.markdown(
    f"""
    <div style="background:#E9DDF0;border-radius:12px;height:26px;width:100%;">
      <div style="background:linear-gradient(90deg,{PURPLE},{PINK});
                  width:{progress * 100:.0f}%;height:100%;border-radius:12px;"></div>
    </div>
    """,
    unsafe_allow_html=True,
)
st.caption(f"{xp:.0f} / {next_xp} XP to reach level {level + 1}")
