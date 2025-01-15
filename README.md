# Start-Shim
`Start-Shim` is a lightweight utility designed to launch an application (primarily GUI programs) while ensuring your terminal regains focus after the application exits. This tool improves productivity by automating window focus management and reducing the need for manual intervention during workflows.

## Features
- Automatically redirects focus back to the terminal after launching GUI apps.
- Streamlines workflows for terminal-based developers and power users.
- Works well with aliases and environment-variable configurations.

## Example Usage
You can create a simple alias using `doskey` to improve your workflow. The alias allows you to seamlessly run GUI-based programs without losing terminal focus.

Example: To run `nvim-qt` (GUI for Neovim) with `start-shim`, configure an alias as follows:
```bash
doskey nv=start-shim nvim-qt $1
```

Then after you exit neovim, even if you have clicked other windows in the meantime, the terminal will regain focus as expected.

## Doskey 
See this [stack overflow](https://superuser.com/a/1858414/1677822) for automatic configuration of doskey aliases.

In my case I ended up modifying `C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat` and added my `doskey` aliases to the end of this batch file.