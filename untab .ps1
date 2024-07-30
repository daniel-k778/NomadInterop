$spacesPerTab = 4

function Convert-TabsToSpaces {
    param (
        [string]$filePath,
        [int]$spacesPerTab
    )

    $content = Get-Content $filePath

    $spaces = " " * $spacesPerTab
    $newContent = $content -replace "`t", $spaces

    Set-Content $filePath -Value $newContent
}

$files = Get-ChildItem -Recurse -Include *.cpp, *.hpp

foreach ($file in $files) {
    Convert-TabsToSpaces -filePath $file.FullName -spacesPerTab $spacesPerTab
    Write-Host "Untabified $($file.FullName)"
}