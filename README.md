# 🐚 Minishell

[![42](https://img.shields.io/badge/42-Project-01BF71?style=flat&logo=42)](https://42.fr)  
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)  

Mini-shell C — implémentation complète d'un shell avec parsing, expansion, redirections, pipes et builtins.

## 📖 Description
Un shell simplifié, inspiré de **bash**, pour comprendre le fonctionnement interne d’un shell :  
- Command parsing  
- Built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)  
- Environment variables expansion  
- Pipes & redirections  

## 👥 Team
- 09125O  
- Othmanebhr  

## ✅ Fonctionnalités principales
- Lexing et parsing robustes (quotes, heredoc, syntax checks)  
- Expansion des variables d'environnement  
- Gestion des heredocs  
- Redirections et pipes  
- Builtins basiques fonctionnels  
- Tests manuels validés  

## 📂 Arborescence (extrait)
- [includes/mini.OD.shell.h](includes/mini.OD.shell.h)  
- [srcs/core](srcs/core) — initialisation et boucle principale (`init_shell`, `process_input`)  
- [srcs/lexer](srcs/lexer) — tokenisation (`lexing`)  
- [srcs/parser](srcs/parser) — parsing, quotes, heredoc  
- [srcs/builder](srcs/builder) — `build_to_exec`  
- [srcs/executor](srcs/executor) — exécution des commandes (`exec`)  
- [libft](libft) — dépendance locale (inclut `get_next_line`)  

## ⚙️ Prérequis & Compilation
- **Prerequisites** : gcc / clang, make, readline (`libreadline-dev`)  
- **Compiler** :
```
make
```
## Nettoyer :
```
make clean
make fclean
L’exécutable final : ./minishell
```
## ▶️ Exécution
```
./minishell
```
Quitter : Ctrl+D ou exit

## 🛠️ Développement & style
Respecter les en-têtes et prototypes (includes/)

Utiliser les fonctions utilitaires de libft (libft/includes/libft.h)

Tests manuels : pipes, redirections, heredoc, expansions

## ⚠️ Debug / erreurs courantes
Vérifier errno avec perror (fork/pipe/open/execve)

Si compilation échoue, vérifier que libft est correctement générée

## 📑 Documentation
Guide Git - Workflow Git pour le projet

## 📌 Fichiers clés
Makefile — compilation

srcs/core/init.c — init_shell, process_input

srcs/lexer/lexer.c — lexing

srcs/parser/parser.c

srcs/builder/builder.c — build_to_exec

srcs/executor/executor.c — exec

libft/srcs/get_next_line/get_next_line.c
