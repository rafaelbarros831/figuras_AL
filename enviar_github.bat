@echo off
chcp 65001 >nul
echo ========================================================
echo   Enviando projeto figuras_AL para o GitHub
echo   Branch: gabriel_trbl
echo   Repo: https://github.com/rafaelbarros831/figuras_AL
echo ========================================================
echo.

set "GIT_CMD=git"
where git >nul 2>nul
if %errorlevel% neq 0 (
    if exist "C:\Program Files\Git\cmd\git.exe" (
        set "GIT_CMD=C:\Program Files\Git\cmd\git.exe"
    ) else if exist "%LOCALAPPDATA%\Programs\Git\cmd\git.exe" (
        set "GIT_CMD=%LOCALAPPDATA%\Programs\Git\cmd\git.exe"
    ) else if exist "C:\Program Files (x86)\Git\cmd\git.exe" (
        set "GIT_CMD=C:\Program Files (x86)\Git\cmd\git.exe"
    )
)

echo [OK] Git localizado: "%GIT_CMD%"
echo.

:: 1. Evita erro de safe directory do Windows
"%GIT_CMD%" config --global --add safe.directory "%CD%"

:: 2. Garante a branch gabriel_trbl e o remote
"%GIT_CMD%" branch -M gabriel_trbl
"%GIT_CMD%" remote remove origin >nul 2>nul
"%GIT_CMD%" remote add origin https://github.com/rafaelbarros831/figuras_AL.git

:: 3. Adiciona todos os arquivos locais e comita
echo [*] Salvando arquivos locais no Git...
"%GIT_CMD%" add .
"%GIT_CMD%" commit -m "Atualizacao completa: versao web interativa e painel de controle de figuras AL"

:: 4. Sincroniza e envia com --force para atualizar a sua branch
echo [*] Atualizando a branch gabriel_trbl no GitHub...
"%GIT_CMD%" push -u origin gabriel_trbl --force

echo.
if %errorlevel% equ 0 (
    echo ========================================================
    echo   [SUCESSO!] Projeto publicado com sucesso!
    echo   Acesse: https://github.com/rafaelbarros831/figuras_AL/tree/gabriel_trbl
    echo ========================================================
) else (
    echo ========================================================
    echo   [ERRO] Nao foi possivel enviar.
    echo   Verifique se sua conta tem permissao na branch.
    echo ========================================================
)

echo.
pause
