# Assembler RISC

Este assembler codifica as instruções propostas no ISA da arquitetura RISC hipotética apresentada na disciplina de ELTD05/ELTD15. 

Utilize o guia do trabalho em que a arquitetura e o ISA são apresentados.

## Descrição

O objetivo deste assembler é facilitar a codificação e a execução das instruções da arquitetura RISC definida para o curso. Ele permite que os usuários escrevam código em uma linguagem de montagem simplificada, que será convertida em código binário compreensível pela máquina.



## ISA da arquitetura proposta

# Tabela de Instruções

## Instruções de Carregamento e Armazenamento

| Instruction Name               | Mnemonic | Format | Encoding (10) | Tamanho em Bits |
|--------------------------------|----------|--------|----------------|------------------|
| Load Byte                      | LB       | I      | 32             | 6 5 5 16         |
| Load Halfword                  | LH       | I      | 33             | 6 5 5 16         |
| Load Word Left                 | LWL      | I      | 34             | 6 5 5 16         |
| Load Word                      | LW       | I      | (Grupo+32)     | 6 5 5 16         |
|                                |          |        | R[rt]=M[R[rs]+SignExtImm] |                  |
| Load Byte Unsigned             | LBU      | I      | 36             | 6 5 5 16         |
| Load Halfword Unsigned         | LHU      | I      | 37             | 6 5 5 16         |
| Load Word Right                | LWR      | I      | 38             | 6 5 5 16         |
| Store Byte                     | SB       | I      | 40             | 6 5 5 16         |
| Store Halfword                 | SH       | I      | 41             | 6 5 5 16         |
| Store Word Left                | SWL      | I      | 42             | 6 5 5 16         |
| Store Word                     | SW       | I      | (Grupo+33)     | 6 5 5 16         |
|                                |          |        | M[R[rs]+SignExtImm]=R[rt] |                  |
| Store Word Right               | SWR      | I      | 46             | 6 5 5 16         |
| Branch on Not Equal            | BNE      | I      | (Grupo+34)     | 6 5 5 16         |
|                                |          |        | if(R[rs] != R[rt]) PC = PC + 4 + offset |  |
| Add Immediate                  | ADDI     | I      | (Grupo+35)     | 6 5 5 16         |
|                                |          |        | R[rt]=R[rs]+SignExtImm |                  |
| Or Immediate                   | ORI      | I      | (Grupo+36)     | 6 5 5 16         |
|                                |          |        | R[rt]=R[rs] | SignExtImm |

## Instruções R

| Mnemonic      | Format | Encoding (10) | Tamanho em Bits |
|---------------|--------|----------------|------------------|
| Add           | ADD    | R      | Grupo+10        | 6 5 5 5 5 6      |
|               |        |            | 10          | 32               |
| Add Unsigned  | ADDU   | R      | 0              | 6 5 5 5 5 6      |
| Subtract      | SUB    | R      | Grupo+10       | 6 5 5 5 5 6      |
| Subtract Unsigned | SUBU | R    | 0              | 6 5 5 5 5 6      |
| Multiplication | MUL   | R      | Grupo+10       | 6 5 5 5 5 6      |
| And           | AND    | R      | Grupo+10       | 6 5 5 5 5 6      |
| Or            | OR     | R      | Grupo+10       | 6 5 5 5 5 6      |
| Exclusive Or  | XOR    | R      | 0              | 6 5 5 5 5 6      |
| Nor           | NOR    | R      | 0              | 6 5 5 5 5 6      |
| Set on Less Than | SLT | R      | 0              | 6 5 5 5 5 6      |
| Set on Less Than Unsigned | SLTU | R  | 0              | 6 5 5 5 5 6      |

## Instruções Imediatas

| Mnemonic                       | Format | Encoding (10) |
|--------------------------------|--------|----------------|
| Add Immediate                  | ADDI   | I      | 8  | $s  | $d | immediate   |
| Add Immediate Unsigned         | ADDIU  | I      | 9  | $s  | $d | immediate   |
| Set on Less Than Immediate     | SLTI   | I      | 10 | $s  | $d | immediate   |
| Set on Less Than Immediate Unsigned | SLTIU | I | 11 | $s  | $d | immediate   |
| And Immediate                  | ANDI   | I      | 12 | $s  | $d | immediate   |
| Or Immediate                   | ORI    | I      | 13 | $s  | $d | immediate   |
| Exclusive Or Immediate         | XORI   | I      | 14 | $s  | $d | immediate   |
| Load Upper Immediate           | LUI    | I      | 15 | 10  | $d | immediate   |

## Instruções de Salto

| Instruction Name               | Mnemonic | Format | Encoding (10) | Tamanho em Bits |
|--------------------------------|----------|--------|----------------|------------------|
| Jump                           | JMP      | J      | 2              | 6 26             |
|                                |          |        | JumpADDR       |                  |
|                                |          |        | PC = JumpADDR  |                  |


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

