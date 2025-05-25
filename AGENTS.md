# Codex Instructions

- Run shellcheck on any shell scripts that are modified. If shellcheck is not installed, try to install it with `apt-get install -y shellcheck`; if that fails due to network issues, document the failure.
- Attempt to execute `.codex/setup.sh` after modifications. Capture the output in `/tmp/setup.log`. Include the last 20 lines of this log in the PR Testing section.
- Commit changes with concise messages summarizing the modifications.

