# Pipex

Um projeto da 42 School que replica o comportamento de redirecionamentos de pipe do shell em C.

## 📋 Descrição

Pipex imita o mecanismo de pipe do shell, permitindo redirecionar a saída de um comando como entrada de outro, enquanto gerencia redirecionamentos de entrada/saída de arquivos.

O programa replica o seguinte comportamento do shell:
```bash
< infile cmd1 | cmd2 > outfile
```

## 🚀 Uso

```bash
./pipex infile "cmd1" "cmd2" outfile
```

### Parâmetros

| Parâmetro | Descrição |
|-----------|-----------|
| `infile`  | Arquivo de entrada (redirecionado para stdin do cmd1) |
| `cmd1`    | Primeiro comando com seus argumentos |
| `cmd2`    | Segundo comando com seus argumentos |
| `outfile` | Arquivo de saída (recebe stdout do cmd2) |

### Exemplos

```bash
# Equivalente a: < input.txt grep hello | wc -l > output.txt
./pipex input.txt "grep hello" "wc -l" output.txt

# Equivalente a: < file.txt cat | head -5 > result.txt
./pipex file.txt "cat" "head -5" result.txt
```

## 🛠️ Compilação

### Clonando

```bash
git clone --recurse-submodules https://github.com/brfialho/pipex.git
```

Se você já clonou sem os submódulos:
```bash
git submodule update --init --recursive
```

### Compilando

```bash
make        # Compila o projeto
make clean  # Remove arquivos objeto
make fclean # Remove arquivos objeto e executável
make re     # Recompila tudo
```

## 📁 Estrutura do Projeto

```
pipex/
├── main.c              # Ponto de entrada
├── main.h              # Arquivo header com structs e protótipos
├── src/
│   ├── child_processes.c   # Lógica de fork e exec
│   ├── destroy.c           # Limpeza de memória e tratamento de erros
│   └── parsing.c           # Parsing de argumentos
├── libft/              # Minha biblioteca libft
├── files/              # Arquivos de teste
└── Makefile
```

## 🔧 Como Funciona

1. **Parsing**: Valida argumentos e extrai comandos
2. **Abrir Arquivos**: Abre arquivo de entrada para leitura, arquivo de saída para escrita
3. **Criar Pipe**: Cria um pipe para comunicação entre processos
4. **Fork de Processos**:
   - **Primeiro filho**: Lê do arquivo de entrada → escreve no pipe
   - **Segundo filho**: Lê do pipe → escreve no arquivo de saída
5. **Espera**: Processo pai espera todos os filhos terminarem
6. **Limpeza**: Fecha descritores de arquivo e libera memória

## 📚 Conceitos Principais

- **`pipe()`**: Cria um canal de dados unidirecional
- **`fork()`**: Cria um processo filho
- **`dup2()`**: Redireciona descritores de arquivo
- **`execv()`**: Substitui o processo atual por um novo programa
- **`waitpid()`**: Espera o processo filho terminar

## ⚠️ Tratamento de Erros

Há tratamento de erros mínimo neste projeto, já que estou fazendo apenas como preparação para o minishell, portanto não será submetido.
O único motivo de ter feito isso é para aprender o básico de pipe.

## 👤 Autor

**brfialho** - Cadete 42

## 📄 Licença

Este projeto faz parte do currículo da 42 School.
