# Assembler RISC

Este assembler codifica as instruções propostas no ISA da arquitetura RISC hipotética apresentada na disciplina de ELTD05/ELTD15. 

Utilize o guia do trabalho em que a arquitetura e o ISA são apresentados.

## Descrição

O objetivo deste assembler é facilitar a codificação e a execução das instruções da arquitetura RISC definida para o curso. Ele permite que os usuários escrevam código em uma linguagem de montagem simplificada, que será convertida em código binário compreensível pela máquina.



## ISA da arquitetura proposta

# Tabela de Instruções

## Instruções de Carregamento e Armazenamento

| Instruction Name               | Mnemonic | Format | Encoding (10)                    |
|--------------------------------|----------|--------|----------------------------------|
| Tamanho em Bits                | -        |   -    | 6        | 5  | 5  | 16          |
| Load Word                      | LW       | I      | Grupo+32 | rs | rt | offset      | R[rt]=M[R[rs]+SignExtImm] |
| Store Word                     | SW       | I      | Grupo+33 | rs | rt | offset      | M[R[rs]+SignExtImm]=R[rt]  |
| Branch on Not Equal            | BNE      | I      | Grupo+34 | rs | rt | offset      | if(R[rs] != R[rt]) PC = PC + 4 + offset |
| Add Immediate                  | ADDI     | I      | Grupo+35 | rs | rt | offset      | R[rt]=R[rs]+SignExtImm |
| Or Immediate                   | ORI      | I      | Grupo+36 | rs | rt | offset      | R[rt]=R[rs] | SignExtImm|


## Instruções R

| Mnemonic      | Format | Encoding (10) | Tamanho em Bits |
|---------------|--------|----------------|------------------|
| Tamanho em Bits | 6 | 5 | 5 | 5 | 5 | 6 |
|                |        | Grupo+10       |                  |
| Add           | ADD    | R      | 32             |
| Subtract      | SUB    | R      | 34             |
| Multiplication | MUL   | R      | 50             |
| And           | AND    | R      | 36             |
| Or            | OR     | R      | 37             |

## Instruções de Salto

| Instruction Name               | Mnemonic | Format | Encoding (10) | Tamanho em Bits |
|--------------------------------|----------|--------|----------------|------------------|
| Tamanho em Bits                | 6 | 26             |                  |
| Jump                           | JMP      | J      | 2              |
|                                |          |        | JumpADDR       |
|                                |          |        | PC = JumpADDR  |



## Funcionalidades

- **Codificação de Instruções**: Suporte para as instruções especificadas no ISA.
- **Geração de Código Binário**: Converte o código de montagem em formato binário.
- **Documentação**: Fornece exemplos e detalhes sobre como usar o assembler.

## Como Usar

1. Escreva seu código de montagem em um  arquivo `xxxxx.asm` (O formato de codificação do assembly pode ser entendido através dos comentários no programa proposto no roteiro do trabalho (prog_avaliacao.hex). Linhas vazias ou comentadas codificarão a instrução NOP em que os 32 bits da instrução são 0. Para esta instrução, tenha cuidado com os sinais de controle a serem gerados no estágio de decodificação. A instrução não pode sobrescrever dados na memória. Ela deve manter o pipeline neutro.
2. Execute o assembler para gerar o arquivo binário correspondente na forma: assembler <input.asm> <grupo> <output.hex>
3. Carregue o arquivo intel hex na memória de programa de sua arquitetura no momento de fazer a síntese do soft core.

## Contribuições

Sinta-se à vontade para contribuir com melhorias e sugestões para este projeto. Para mais informações, consulte o guia do trabalho da disciplina.

## Licença

Este projeto está sob a licença [MIT](LICENSE).

