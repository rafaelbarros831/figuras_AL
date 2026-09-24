# Script PowerShell atualizado com --force
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

Write-Host "========================================================" -ForegroundColor Cyan
Write-Host "  Enviando figuras_AL para GitHub (Branch: gabriel_trbl) " -ForegroundColor Cyan
Write-Host "========================================================" -ForegroundColor Cyan

$gitCmd = "git"
if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
    $caminhos = @(
        "C:\Program Files\Git\cmd\git.exe",
        "$env:LOCALAPPDATA\Programs\Git\cmd\git.exe",
        "C:\Program Files (x86)\Git\cmd\git.exe"
    )
    $encontrado = $caminhos | Where-Object { Test-Path $_ } | Select-Object -First 1
    if ($encontrado) { $gitCmd = $encontrado }
}

Write-Host "[OK] Git: $gitCmd" -ForegroundColor Green

& $gitCmd config --global --add safe.directory (Get-Location).Path
& $gitCmd branch -M gabriel_trbl
& $gitCmd remote remove origin 2>$null
& $gitCmd remote add origin https://github.com/rafaelbarros831/figuras_AL.git

Write-Host "[*] Comitando alteracoes..." -ForegroundColor Yellow
& $gitCmd add .
& $gitCmd commit -m "Atualizacao completa: versao web interativa e painel de figuras AL"

Write-Host "[*] Enviando com --force para a branch gabriel_trbl..." -ForegroundColor Cyan
& $gitCmd push -u origin gabriel_trbl --force

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n[SUCESSO!] Projeto publicado com sucesso!" -ForegroundColor Green
    Write-Host "Link: https://github.com/rafaelbarros831/figuras_AL/tree/gabriel_trbl" -ForegroundColor Cyan
} else {
    Write-Host "`n[ERRO] Falha ao enviar para o GitHub." -ForegroundColor Red
}
