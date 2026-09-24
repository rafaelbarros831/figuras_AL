# Script PowerShell para enviar o projeto ao GitHub
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

Write-Host "========================================================" -ForegroundColor Cyan
Write-Host "  Enviando figuras_AL para GitHub (Branch: gabriel_trbl) " -ForegroundColor Cyan
Write-Host "========================================================" -ForegroundColor Cyan

# 1. Procura o Git
$gitCmd = "git"
if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
    $caminhos = @(
        "C:\Program Files\Git\cmd\git.exe",
        "$env:LOCALAPPDATA\Programs\Git\cmd\git.exe",
        "C:\Program Files (x86)\Git\cmd\git.exe"
    )
    $encontrado = $caminhos | Where-Object { Test-Path $_ } | Select-Object -First 1
    if ($encontrado) {
        $gitCmd = $encontrado
    } else {
        Write-Host "Git nao encontrado. Tentando instalar via winget..." -ForegroundColor Yellow
        winget install --id Git.Git -e --source winget
        if (Test-Path "C:\Program Files\Git\cmd\git.exe") {
            $gitCmd = "C:\Program Files\Git\cmd\git.exe"
        } else {
            Write-Host "Instale o Git em https://git-scm.com/download/win e tente novamente." -ForegroundColor Red
            exit 1
        }
    }
}

Write-Host "[OK] Usando Git: $gitCmd" -ForegroundColor Green

# 2. Inicializa o repositorio se nao existir
if (-not (Test-Path ".git")) {
    Write-Host "[*] Inicializando git init..." -ForegroundColor Yellow
    & $gitCmd init
}

# 3. Configura safe directory e branch
& $gitCmd config --global --add safe.directory (Get-Location).Path
& $gitCmd branch -M gabriel_trbl

# 4. Configura remote
Write-Host "[*] Configurando repositorio remoto..." -ForegroundColor Yellow
& $gitCmd remote remove origin 2>$null
& $gitCmd remote add origin https://github.com/rafaelbarros831/figuras_AL.git

# 5. Adiciona arquivos e commit
Write-Host "[*] Adicionando arquivos..." -ForegroundColor Yellow
& $gitCmd add .

Write-Host "[*] Criando commit..." -ForegroundColor Yellow
& $gitCmd commit -m "Atualizacao completa: versao web interativa, painel de controle e transformacoes de figuras AL"

# 6. Push para a branch gabriel_trbl
Write-Host "[*] Enviando para o GitHub..." -ForegroundColor Cyan
& $gitCmd push -u origin gabriel_trbl

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n[SUCESSO] Projeto publicado na branch gabriel_trbl!" -ForegroundColor Green
    Write-Host "Link: https://github.com/rafaelbarros831/figuras_AL/tree/gabriel_trbl" -ForegroundColor Cyan
} else {
    Write-Host "`n[AVISO] Se solicitou login, faca a autenticacao no navegador." -ForegroundColor Yellow
}
