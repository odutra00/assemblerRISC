# Assembler RISC

Este assembler codifica as instruções propostas no ISA da arquitetura RISC hipotética apresentada na disciplina de ELTD05/ELTD15. 

Utilize o guia do trabalho em que a arquitetura e o ISA são apresentados.

## Descrição

O objetivo deste assembler é facilitar a codificação e a execução das instruções da arquitetura RISC definida para o curso. Ele permite que os usuários escrevam código em uma linguagem de montagem simplificada, que será convertida em código binário compreensível pela máquina.



<!-- ## ISA da arquitetura proposta

# Tabela de Instruções

## Instruções de Carregamento e Armazenamento

| Instruction Name               | Mnemonic | Format | Encoding (10)                    | Meaning                                   |
|--------------------------------|----------|--------|----------------------------------|-------------------------------------------|
| Tamanho em Bits                | -        |   -    | 6        | 5  | 5  | 16          |                                           |
| Load Word                      | LW       | I      | Grupo+32 | rs | rt | offset      | R[rt]=M[R[rs]+SignExtImm]                 |
| Store Word                     | SW       | I      | Grupo+33 | rs | rt | offset      | M[R[rs]+SignExtImm]=R[rt]                 |
| Branch on Not Equal            | BNE      | I      | Grupo+34 | rs | rt | offset      | if(R[rs] != R[rt]) PC = PC + 4 + offset   |
| Add Immediate                  | ADDI     | I      | Grupo+35 | rs | rt | offset      | R[rt]=R[rs]+SignExtImm                    |
| Or Immediate                   | ORI      | I      | Grupo+36 | rs | rt | offset      | R[rt]=R[rs] or SignExtImm                 |


## Instruções R

| Instruction Name  | Mnemonic  |     Format    | Encoding (10)                      | Meaning                              |
|-------------------|-----------|----------------------------------------------------|--------------------------------------|
| Tamanho em Bits   |   -             -         | 6         | 5  | 5  | 5  | 5  | 6  |          -                           |
| Addition          | ADD       | R             | Grupo+10  | rs | rt | rd | 10 | 32 | R[rd]=R[rs]+R[rt]                    |
| Subtract          | SUB       | R             | Grupo+10  | rs | rt | rd | 10 | 34 | R[rd]=R[rs]-R[rt]                    |
| Multiplication    | MUL       | R             | Grupo+10  | rs | rt | rd | 10 | 50 | R[rd] = lowerHW_R[rs] * lowerHW_R[rt]|    
| And               | AND       | R             | Grupo+10  | rs | rt | rd | 10 | 36 | R[rd]=R[rs]&R[rt]                    |
| Or                | OR        | R             | Grupo+10  | rs | rt | rd | 10 | 37 | R[rd]=R[rs]|R[rt]                    |

## Instruções de Salto

| Instruction Name               | Mnemonic | Format    | Encoding (10) | Meaning           |
|--------------------------------|----------|-----------|---------------|-------------------|
| Tamanho em Bits                     -          -      | 6 |       26  |        -          | 
| Jump                           | JMP      | J         | 2 | JumpADDR  |  PC = JumpADDR    |

## Special Instruction

| Instruction Name               | Mnemonic | Format    | Encoding (10) | Meaning           |
|--------------------------------|----------|-----------|---------------|-------------------|
| Tamanho em Bits                     -          -      |    32         |        -          | 
| No Operation                   |          |    -      |     0         | No operation      |


-->


<h2>Tabela de Instruções</h2>

<h3>Instruções de Carregamento e Armazenamento</h3>

<table>
  <thead>
    <tr>
      <th>Instruction Name</th>
      <th>Mnemonic</th>
      <th>Format</th>
      <th>Encoding (10)</th>
      <th>Meaning</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Tamanho em Bits</td>
      <td>-</td>
      <td>-</td>
      <td>6 | 5 | 5 | 16</td>
      <td>-</td>
    </tr>
    <tr>
      <td>Load Word</td>
      <td>LW</td>
      <td>I</td>
      <td>Grupo+32 | rs | rt | offset</td>
      <td>R[rt]=M[R[rs]+SignExtImm]</td>
    </tr>
    <tr>
      <td>Store Word</td>
      <td>SW</td>
      <td>I</td>
      <td>Grupo+33 | rs | rt | offset</td>
      <td>M[R[rs]+SignExtImm]=R[rt]</td>
    </tr>
    <tr>
      <td>Branch on Not Equal</td>
      <td>BNE</td>
      <td>I</td>
      <td>Grupo+34 | rs | rt | offset</td>
      <td>if(R[rs] != R[rt]) PC = PC + 4 + offset</td>
    </tr>
    <tr>
      <td>Add Immediate</td>
      <td>ADDI</td>
      <td>I</td>
      <td>Grupo+35 | rs | rt | offset</td>
      <td>R[rt]=R[rs]+SignExtImm</td>
    </tr>
    <tr>
      <td>Or Immediate</td>
      <td>ORI</td>
      <td>I</td>
      <td>Grupo+36 | rs | rt | offset</td>
      <td>R[rt]=R[rs] or SignExtImm</td>
    </tr>
  </tbody>
</table>

<h3>Instruções R</h3>

<table>
  <thead>
    <tr>
      <th>Instruction Name</th>
      <th>Mnemonic</th>
      <th>Format</th>
      <th>Encoding (10)</th>
      <th>Meaning</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Tamanho em Bits</td>
      <td>-</td>
      <td>-</td>
      <td>6 | 5 | 5 | 5 | 5 | 6</td>
      <td>-</td>
    </tr>
    <tr>
      <td>Addition</td>
      <td>ADD</td>
      <td>R</td>
      <td>Grupo+10 | rs | rt | rd | 10 | 32</td>
      <td>R[rd]=R[rs]+R[rt]</td>
    </tr>
    <tr>
      <td>Subtract</td>
      <td>SUB</td>
      <td>R</td>
      <td>Grupo+10 | rs | rt | rd | 10 | 34</td>
      <td>R[rd]=R[rs]-R[rt]</td>
    </tr>
    <tr>
      <td>Multiplication</td>
      <td>MUL</td>
      <td>R</td>
      <td>Grupo+10 | rs | rt | rd | 10 | 50</td>
      <td>R[rd] = lowerHW_R[rs] * lowerHW_R[rt]</td>
    </tr>
    <tr>
      <td>And</td>
      <td>AND</td>
      <td>R</td>
      <td>Grupo+10 | rs | rt | rd | 10 | 36</td>
      <td>R[rd]=R[rs]&R[rt]</td>
    </tr>
    <tr>
      <td>Or</td>
      <td>OR</td>
      <td>R</td>
      <td>Grupo+10 | rs | rt | rd | 10 | 37</td>
      <td>R[rd]=R[rs]|R[rt]</td>
    </tr>
  </tbody>
</table>

<h3>Instruções de Salto</h3>

<table>
  <thead>
    <tr>
      <th>Instruction Name</th>
      <th>Mnemonic</th>
      <th>Format</th>
      <th>Encoding (10)</th>
      <th>Meaning</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Tamanho em Bits</td>
      <td>-</td>
      <td>-</td>
      <td>6 | 26</td>
      <td>-</td>
    </tr>
    <tr>
      <td>Jump</td>
      <td>JMP</td>
      <td>J</td>
      <td>2 | JumpADDR</td>
      <td>PC = JumpADDR</td>
    </tr>
  </tbody>
</table>

<h3>Special Instruction</h3>

<table>
  <thead>
    <tr>
      <th>Instruction Name</th>
      <th>Mnemonic</th>
      <th>Format</th>
      <th>Encoding (10)</th>
      <th>Meaning</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>Tamanho em Bits</td>
      <td>-</td>
      <td>-</td>
      <td>32</td>
      <td>-</td>
    </tr>
    <tr>
      <td>No Operation</td>
      <td>-</td>
      <td>-</td>
      <td>0</td>
      <td>No operation</td>
    </tr>
  </tbody>
</table>




## Funcionalidades

- **Codificação de Instruções**: Suporte para as instruções especificadas no ISA.
- **Geração de Código Binário**: Converte o código de montagem em formato binário.
- **Documentação**: Fornece exemplos e detalhes sobre como usar o assembler.

## Como Usar

1. Escreva seu código de montagem em um  arquivo `xxxxx.asm` (O formato de codificação do assembly pode ser entendido através dos comentários no programa proposto no roteiro do trabalho (prog_avaliacao.hex). Linhas vazias ou comentadas codificarão a instrução NOP em que os 32 bits da instrução são 0. Para esta instrução, tenha cuidado com os sinais de controle a serem gerados no estágio de decodificação. A instrução não pode sobrescrever dados na memória / register file. Ela deve manter o pipeline neutro.
2. Execute o assembler para gerar o arquivo binário correspondente na forma: **assembler input.asm grupo output.hex** .
3. Carregue o arquivo intel hex na memória de programa de sua arquitetura no momento de fazer a síntese do soft core.

## Contribuições

Sinta-se à vontade para contribuir com melhorias e sugestões para este projeto. Para mais informações, consulte o guia do trabalho da disciplina.

## Licença

Este projeto está sob a licença [MIT](LICENSE).

