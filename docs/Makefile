# Makefile for building OpenMach documentation using Doxygen and Sphinx

# Resolve this Makefile's directory to handle invocation from any path
THIS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

DOXYFILE  := $(THIS_DIR)/Doxyfile
SPHINXDIR := $(THIS_DIR)/sphinx
BUILDDIR  := $(THIS_DIR)/build

.PHONY: all doxygen html clean

# Default target builds the HTML documentation
all: html

# Run Doxygen to generate XML output consumed by Breathe

doxygen:
@doxygen $(DOXYFILE)

# Generate Sphinx HTML documentation using the Breathe extension
html: doxygen
@sphinx-build -b html $(SPHINXDIR) $(BUILDDIR)/html

# Remove generated documentation artifacts
clean:
@rm -rf $(BUILDDIR)

