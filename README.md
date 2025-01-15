# start-shim
`start-shim` is a utility that launches an application while ensuring your terminal regains focus after the application exits. 

## Example Usage
You can create a simple alias using `doskey`.

Example: To run `nvim-qt` (GUI for Neovim) with `start-shim`, configure an alias as follows:
```bash
doskey nv=start-shim nvim-qt $1
```

Then after you exit neovim-qt, even if you have clicked other windows in the meantime, the terminal will regain focus as desired.

## Doskey 
See this [stack overflow](https://superuser.com/a/1858414/1677822) for automatic configuration of doskey aliases.

In my case I ended up modifying `C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat` and added my `doskey` aliases to the end of this batch file.
