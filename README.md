# Phoenix Robotics Build Season 2016

Repository for 2016 FRC Build Season.


### Line endings

To keep line endings consistent between WIndows and Unix development systems see [Dealing with line endings] (https://help.github.com/articles/dealing-with-line-endings/#platform-all) for full details.

The `.gitattributes` file has been created.

Please run the following on OS X and Linux:

```bash
git config --global core.autocrlf input
# Configure Git on OS X or Linux to properly handle line endings
```
Or run the following on Windows

```bash
git config --global core.autocrlf true
# Configure Git on Windows to properly handle line endings
```

### Fix CRLFs in directory
```bash
 find ./ -type f -exec sed -i -e 's/^M$//g' {} \;
 # Or, much more concisely:
 sed -i 's/^M//g' *
```
