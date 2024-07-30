$cppFiles = Get-ChildItem -Path . -Filter *.cpp

foreach ($file in $cppFiles) {
    Remove-Item -Path $file.FullName -Force
}

Write-Host "All .cpp files have been deleted from the current directory."