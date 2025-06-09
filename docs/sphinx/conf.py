"""Sphinx configuration for the OpenMach project."""

from __future__ import annotations

import os
import sys
from datetime import datetime

# Add project root to ``sys.path`` so that extensions can locate modules.
sys.path.insert(0, os.path.abspath("../.."))

# General project information
project = "OpenMach"
author = "OpenMach Developers"
# The full version, including alpha/beta/rc tags
release = "0.1"

# Enable Breathe extension to integrate Doxygen output
extensions = [
    "breathe",
    "sphinx_rtd_theme",
]

# Map Breathe project name to the directory containing Doxygen's XML output
breathe_projects = {
    "openmach": os.path.abspath("../build/xml"),
}

# Set the default Breathe project
breathe_default_project = "openmach"

# Use the Read the Docs theme for clean documentation appearance
html_theme = "sphinx_rtd_theme"

# Include source file timestamps in the documentation
html_last_updated_fmt = "%b %d, %Y"

