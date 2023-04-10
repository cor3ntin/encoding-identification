set "filename=%1"
powershell -Command "(gc %filename%) -replace '#pragma once', '' | Out-File %filename%"
