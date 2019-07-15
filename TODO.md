TODO:

- [ ] Saídas do programa
    - [ ] Programa assembly
    - [ ] Binário gerado
    - [ ] Dados da Previsão de Desvio
        - [ ] Total de saltos
        - [ ] Acertos
        - [ ] Erros
    - [ ] Número de ciclos
    - [ ] Instruções
        - [ ] Emitidas
        - [ ] Efetivadas (%)
    - [ ] Execução --detail (em cada ciclo, imprime as instruções no)
        - [ ] Estágio de busca
        - [ ] Estágio de execução
        - [ ] Estágio de alinhamento
        - [ ] Estágio de escrita
        - [ ] Efetivando
        - [ ] Bypassing

- [x] Parâmetros do Programa
    - [x] --detail (execução detalhada)
    - [x] -m (tamanho da memória)
    - [x] -i (arquivo assembly contendo o programa a ser simulado)
    - [x] -o (arquivo de saída contendo o programa convertido para binário)
    - [x] -h (help)
 
- [x] Implementar previsão de Desvio no estágio de busca
    - [x] Decoding da operação
        - [x] Opcode
        - [x] Operandos
    - [x] Ler a quantidade de bytes do opcode de salto.
    - [x] Atualizar PC de acordo com o offset.

- [ ] Implementar o estágio de execução
    - [ ] Criar unidades funcionais (deixar suporte à escalabilidade)
        - [ ] (2x) PF_Mult 
        - [ ] (1x) PF_Div
        - [ ] (1x) PF_Add
        - [ ] (1x) Int
    - [ ] Execução da instrução

<!-- TODO Saber o que é isso -->
- [ ] Suporte ao Bypassing
- [ ] Estágio de alinhamento
<!-- -->

<!-- Acredito que nesse estágio, as operações que tem um registrador
 destino irão escrever seus resultados no tal registrador; 
As que não tiverem, apenas passam por aqui, sem escrever em lugar nenhum; 
TODO Confirmar teoria -->
- [ ] Estágio de escrita
    - [ ] Escrever resultados no destino

- [ ] Suporte ao scoreboarding
    - [ ] Emissão
        - [ ] Verificar se UF está livre
        - [ ] Verificar se não existe WAW
    - [ ] Leitura dos Operandos
        - [ ] Esperar RAW
    - [ ] Execução
    - [ ] Escrita dos operandos
        - [ ] Esperar WAR
