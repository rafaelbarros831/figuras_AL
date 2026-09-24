@echo off
chcp 65001 >nul
echo ========================================================
echo   Enviando projeto figuras_AL para o GitHub
echo   Branch: gabriel_trbl
echo   Repo: https://github.com/rafaelbarros831/figuras_AL
echo ========================================================
echo.

:: 1. Procura o executavel do Git
set "GIT_CMD=git"
where git >nul 2>nul
if %errorlevel% neq 0 (
    if exist "C:\Program Files\Git\cmd\git.exe" (
        set "GIT_CMD=C:\Program Files\Git\cmd\git.exe"
    ) else if exist "%LOCALAPPDATA%\Programs\Git\cmd\git.exe" (
        set "GIT_CMD=%LOCALAPPDATA%\Programs\Git\cmd\git.exe"
    ) else if exist "C:\Program Files (x86)\Git\cmd\git.exe" (
        set "GIT_CMD=C:\Program Files (x86)\Git\cmd\git.exe"
    ) else (
        echo [AVISO] Git nao foi encontrado no sistema!
        echo Tentando instalar automaticamente via winget...
        winget install --id Git.Git -e --source winget
        if exist "C:\Program Files\Git\cmd\git.exe" (
            set "GIT_CMD=C:\Program Files\Git\cmd\git.exe"
        ) else (
            echo.
            echo [ERRO] Nao foi possivel localizar o Git.
            echo Por favor, instale o Git baixando de: https://git-scm.com/download/win
            pause
            exit /b 1
        )
    )
)

echo [OK] Git localizado: "%GIT_CMD%"
echo.

:: 2. Inicializa o repositorio se necessario
if not exist ".git" (
    echo [*] Inicializando repositorio local Git...
    "%GIT_CMD%" init
)

:: 3. Configura a branch gabriel_trbl
echo [*] Configurando branch 'gabriel_trbl'...
"%GIT_CMD%" branch -M gabriel_trbl

:: 4. Configura o remote origin
echo [*] Configurando repositorio remoto...
"%GIT_CMD%" remote remove origin >nul 2>nul
"%GIT_CMD%" remote add origin https://github.com/rafaelbarros831/figuras_AL.git

:: 5. Adiciona todos os arquivos
echo [*] Adicionando arquivos do projeto...
"%GIT_CMD%" add .

:: 6. Realiza o commit
echo [*] Criando commit...
"%GIT_CMD%" commit -m "Atualizacao completa: versao web interativa, painel de controle e transformacoes de figuras AL"

:: 7. Envia para o GitHub na branch gabriel_trbl
echo.
echo [*] Enviando para o GitHub (pode abrir janela de login no navegador)...
"%GIT_CMD%" push -u origin gabriel_trbl

echo.
if %errorlevel% equ 0 (
    echo ========================================================
    echo   [SUCESSO] Projeto enviado com sucesso para a branch!
    echo   Acesse: https://github.com/rafaelbarros831/figuras_AL/tree/gabriel_trbl
    echo ========================================================
) else (
    echo ========================================================
    echo   [AVISO] Verifique se voce tem permissao de escrita no
    echo   repositorio ou se fez login com sua conta do GitHub.
    echo ========================================================
)

echo.
pause
