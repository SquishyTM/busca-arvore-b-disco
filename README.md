#### Problema

Implemente a busca de uma chave X em uma árvore B de ordem d armazenada em disco. A chave da árvore é o código do cliente. A busca começa na raiz e, em cada nó, decide se a chave está no próprio nó ou em qual dos filhos ela pode estar, até encontrar a chave ou chegar a uma folha sem encontrá-la.

A lógica é a mesma da busca em árvore B em memória principal vista anteriormente (funções posicao e busca). A diferença é que os nós estão gravados em arquivo e, portanto, precisam ser lidos do arquivo. Como cada leitura de nó é um acesso a disco, **cada nó deve ser lido no máximo uma vez** — o programa também imprime a quantidade de nós lidos, que deve ser no máximo a altura da árvore.

A árvore é armazenada em dois arquivos:

- **Arquivo de metadados** (metadados.dat): contém a ordem d da árvore, o ponteiro para a raiz (pont\_raiz) e o ponteiro para a próxima posição livre do arquivo de dados (pont\_prox\_no\_livre). Uma árvore vazia tem pont\_raiz igual a -1.
- **Arquivo de dados** (clientes.dat): contém os nós da árvore. Cada nó guarda a quantidade de chaves (m), o ponteiro para o nó pai (pont\_pai), os ponteiros para os filhos (p) e os clientes. Ponteiros nulos valem -1.

Todos os ponteiros são posições (em bytes) dentro do arquivo de dados. A busca **não altera** nenhum dos dois arquivos.

O arquivo arvore\_b.c fornecido já contém as seguintes funções prontas:

- le\_no\_pos: lê um nó de uma posição do arquivo de dados
- posicao: busca binária da posição em que a chave deveria estar dentro do nó

Vocês devem implementar as funções:

- TCliente \*busca\_no(FILE \*arq, int d, int ptNo, int chave, int \*pt\_no, int \*qtd\_nos\_lidos): busca a chave na subárvore cuja raiz está gravada na posição ptNo do arquivo de dados. Retorna uma cópia do cliente encontrado (criada com a função cliente), ou NULL caso a chave não exista. Grava em \*pt\_no a posição do nó onde a chave foi encontrada (ou -1, caso ela não exista) e incrementa \*qtd\_nos\_lidos uma vez para cada nó lido do arquivo
- TCliente \*busca(int chave, char \*nome\_arquivo\_metadados, char \*nome\_arquivo\_dados, int d, int \*pt\_no, int \*qtd\_nos\_lidos): abre os arquivos, trata o caso da árvore vazia e busca a chave a partir da raiz. Retorna o cliente encontrado (ou NULL), gravando em \*pt\_no a posição do nó onde a chave foi encontrada (ou -1) e em \*qtd\_nos\_lidos a quantidade de nós lidos do arquivo de dados durante a busca

Use o arquivo arvore\_b.c fornecido nesse exercício, pois ele já contém o tratamento de entrada e saída.

#### Entrada:
- Código do cliente (chave X) a ser buscado
- Os arquivos metadados.dat e clientes.dat com a árvore, que devem estar no diretório onde o programa é executado (eles não são lidos do teclado). Cada caso de teste fornece esses dois arquivos

#### Saída:
- A linha "PONT " seguida da posição (no arquivo de dados) do nó onde a chave foi encontrada, ou -1 caso a chave não exista na árvore
- A linha "CLIENTE:" seguida do cliente encontrado (código e nome). Se a chave não existir na árvore, nada é impresso depois dessa linha
- A linha "NOS LIDOS: " seguida da quantidade de nós lidos do arquivo de dados durante a busca

## Árvores usadas nos casos de teste

Em todas as árvores, d = 2 (cada nó tem no mínimo 2 e no máximo 4 chaves) e cada nó ocupa 444 bytes no arquivo de dados. Logo, os nós estão nas posições 0, 444, 888, 1332, ... do arquivo de dados. Nos desenhos, a posição de cada nó aparece embaixo dele.

As árvores foram montadas inserindo os clientes na ordem indicada em "Clientes inseridos", com o mesmo algoritmo de inserção do exercício anterior.

### Árvore A: árvore vazia

Clientes inseridos: nenhum

```
ARQUIVO DE METADADOS:
2, -1, 0
ARQUIVO DE DADOS:
```

### Árvore B: um único nó (a raiz é uma folha)

Clientes inseridos: 10:Joao-11:Vanessa-13:Maria

```
    [10, 11, 13]
        pos 0
```

```
ARQUIVO DE METADADOS:
2, 0, 444
ARQUIVO DE DADOS:
NO: 3, -1, (-1, -1, -1, -1, -1)
	10, Joao
	11, Vanessa
	13, Maria
```

### Árvore C: dois níveis

Clientes inseridos: 10:Ana-15:Paulo-20:Bia-25:Rui-30:Caio-40:Davi-50:Eva-60:Fabio-70:Gil-80:Hugo

```
                        [20, 40]
                         pos 888
             /              |              \
      [10, 15]          [25, 30]      [50, 60, 70, 80]
       pos 0             pos 444          pos 1332
```

```
ARQUIVO DE METADADOS:
2, 888, 1776
ARQUIVO DE DADOS:
NO: 2, 888, (-1, -1, -1, -1, -1)
	10, Ana
	15, Paulo
NO: 2, 888, (-1, -1, -1, -1, -1)
	25, Rui
	30, Caio
NO: 2, -1, (0, 444, 1332, -1, -1)
	20, Bia
	40, Davi
NO: 4, 888, (-1, -1, -1, -1, -1)
	50, Eva
	60, Fabio
	70, Gil
	80, Hugo
```

### Árvore D: três níveis

Clientes inseridos: 10:Ana-20:Bia-30:Caio-40:Davi-50:Eva-60:Fabio-70:Gil-80:Hugo-90:Ivo-100:Joao-110:Lia-120:Malu-130:Nina-140:Otto-150:Paulo-160:Rui-170:Sara-180:Tina-190:Ugo-200:Vera-210:Will-220:Yuri-230:Zeca-240:Alice

```
                                        [90]
                                      pos 3552
                   /                                        \
            [30, 60]                              [120, 150, 180, 210]
            pos 888                                      pos 3108
       /       |       \                 /          |          |          |          \
[10, 20] [40, 50] [70, 80]     [100, 110] [130, 140] [160, 170] [190, 200] [220, 230, 240]
  pos 0   pos 444  pos 1332      pos 1776   pos 2220   pos 2664   pos 3996     pos 4440
```

```
ARQUIVO DE METADADOS:
2, 3552, 4884
ARQUIVO DE DADOS:
NO: 2, 888, (-1, -1, -1, -1, -1)
	10, Ana
	20, Bia
NO: 2, 888, (-1, -1, -1, -1, -1)
	40, Davi
	50, Eva
NO: 2, 3552, (0, 444, 1332, -1, -1)
	30, Caio
	60, Fabio
NO: 2, 888, (-1, -1, -1, -1, -1)
	70, Gil
	80, Hugo
NO: 2, 3108, (-1, -1, -1, -1, -1)
	100, Joao
	110, Lia
NO: 2, 3108, (-1, -1, -1, -1, -1)
	130, Nina
	140, Otto
NO: 2, 3108, (-1, -1, -1, -1, -1)
	160, Rui
	170, Sara
NO: 4, 3552, (1776, 2220, 2664, 3996, 4440)
	120, Malu
	150, Paulo
	180, Tina
	210, Will
NO: 1, -1, (888, 3108, -1, -1, -1)
	90, Ivo
NO: 2, 3108, (-1, -1, -1, -1, -1)
	190, Ugo
	200, Vera
NO: 3, 3108, (-1, -1, -1, -1, -1)
	220, Yuri
	230, Zeca
	240, Alice
```

## Exemplos

|Árvore|Entrada|Saída|Explicação|
|---|---|---|---|
|[A](#árvore-a-árvore-vazia)|10|PONT -1<BR/>CLIENTE:<BR/>NOS LIDOS: 0|A árvore está vazia (pont\_raiz é -1): nenhum nó precisa ser lido|
|[B](#árvore-b-um-único-nó-a-raiz-é-uma-folha)|11|PONT 0<BR/>CLIENTE:<BR/>&emsp;11, Vanessa<BR/>NOS LIDOS: 1|A chave está na raiz, que é a única folha da árvore|
|[C](#árvore-c-dois-níveis)|20|PONT 888<BR/>CLIENTE:<BR/>&emsp;20, Bia<BR/>NOS LIDOS: 1|A chave está na raiz: a busca termina sem descer para as folhas|
|[C](#árvore-c-dois-níveis)|70|PONT 1332<BR/>CLIENTE:<BR/>&emsp;70, Gil<BR/>NOS LIDOS: 2|70 é maior que 20 e que 40, então a busca desce para o filho da direita da raiz|
|[C](#árvore-c-dois-níveis)|5|PONT -1<BR/>CLIENTE:<BR/>NOS LIDOS: 2|5 é menor que todas as chaves: a busca desce para o filho da esquerda da raiz e chega numa folha sem encontrar a chave|
|[D](#árvore-d-três-níveis)|170|PONT 2664<BR/>CLIENTE:<BR/>&emsp;170, Sara<BR/>NOS LIDOS: 3|A chave está numa folha do nível mais baixo: a busca lê um nó por nível|
|[D](#árvore-d-três-níveis)|175|PONT -1<BR/>CLIENTE:<BR/>NOS LIDOS: 3|A chave não existe: a busca desce até a folha onde ela deveria estar|

## Casos de teste:

Os casos de teste estão na pasta [casos-teste](casos-teste). Cada caso tem 4 arquivos:

- entrada.txt: o que deve ser digitado no teclado (a chave a ser buscada)
- metadados.dat e clientes.dat: a árvore onde a busca é feita (arquivos binários)
- saida.txt: a saída esperada do programa

|Caso|Árvore|Chave|Descrição|Arquivos|
|---|---|---|---|---|
|[1](casos-teste/1)|[A](#árvore-a-árvore-vazia)|10|Árvore vazia: nenhum nó é lido|[entrada.txt](casos-teste/1/entrada.txt) [metadados.dat](casos-teste/1/metadados.dat) [clientes.dat](casos-teste/1/clientes.dat) [saida.txt](casos-teste/1/saida.txt)|
|[2](casos-teste/2)|[B](#árvore-b-um-único-nó-a-raiz-é-uma-folha)|11|Chave na raiz, que é uma folha|[entrada.txt](casos-teste/2/entrada.txt) [metadados.dat](casos-teste/2/metadados.dat) [clientes.dat](casos-teste/2/clientes.dat) [saida.txt](casos-teste/2/saida.txt)|
|[3](casos-teste/3)|[B](#árvore-b-um-único-nó-a-raiz-é-uma-folha)|12|Chave não existe numa árvore com um único nó|[entrada.txt](casos-teste/3/entrada.txt) [metadados.dat](casos-teste/3/metadados.dat) [clientes.dat](casos-teste/3/clientes.dat) [saida.txt](casos-teste/3/saida.txt)|
|[4](casos-teste/4)|[C](#árvore-c-dois-níveis)|20|Chave na raiz, que é um nó interno|[entrada.txt](casos-teste/4/entrada.txt) [metadados.dat](casos-teste/4/metadados.dat) [clientes.dat](casos-teste/4/clientes.dat) [saida.txt](casos-teste/4/saida.txt)|
|[5](casos-teste/5)|[C](#árvore-c-dois-níveis)|15|Chave na folha mais à esquerda|[entrada.txt](casos-teste/5/entrada.txt) [metadados.dat](casos-teste/5/metadados.dat) [clientes.dat](casos-teste/5/clientes.dat) [saida.txt](casos-teste/5/saida.txt)|
|[6](casos-teste/6)|[C](#árvore-c-dois-níveis)|70|Chave na folha mais à direita|[entrada.txt](casos-teste/6/entrada.txt) [metadados.dat](casos-teste/6/metadados.dat) [clientes.dat](casos-teste/6/clientes.dat) [saida.txt](casos-teste/6/saida.txt)|
|[7](casos-teste/7)|[C](#árvore-c-dois-níveis)|5|Chave menor que todas as chaves da árvore|[entrada.txt](casos-teste/7/entrada.txt) [metadados.dat](casos-teste/7/metadados.dat) [clientes.dat](casos-teste/7/clientes.dat) [saida.txt](casos-teste/7/saida.txt)|
|[8](casos-teste/8)|[C](#árvore-c-dois-níveis)|99|Chave maior que todas as chaves da árvore|[entrada.txt](casos-teste/8/entrada.txt) [metadados.dat](casos-teste/8/metadados.dat) [clientes.dat](casos-teste/8/clientes.dat) [saida.txt](casos-teste/8/saida.txt)|
|[9](casos-teste/9)|[D](#árvore-d-três-níveis)|90|Chave na raiz de uma árvore com 3 níveis|[entrada.txt](casos-teste/9/entrada.txt) [metadados.dat](casos-teste/9/metadados.dat) [clientes.dat](casos-teste/9/clientes.dat) [saida.txt](casos-teste/9/saida.txt)|
|[10](casos-teste/10)|[D](#árvore-d-três-níveis)|150|Chave num nó interno do nível 2|[entrada.txt](casos-teste/10/entrada.txt) [metadados.dat](casos-teste/10/metadados.dat) [clientes.dat](casos-teste/10/clientes.dat) [saida.txt](casos-teste/10/saida.txt)|
|[11](casos-teste/11)|[D](#árvore-d-três-níveis)|170|Chave numa folha do nível 3|[entrada.txt](casos-teste/11/entrada.txt) [metadados.dat](casos-teste/11/metadados.dat) [clientes.dat](casos-teste/11/clientes.dat) [saida.txt](casos-teste/11/saida.txt)|
|[12](casos-teste/12)|[D](#árvore-d-três-níveis)|175|Chave não existe: a busca desce até uma folha do nível 3|[entrada.txt](casos-teste/12/entrada.txt) [metadados.dat](casos-teste/12/metadados.dat) [clientes.dat](casos-teste/12/clientes.dat) [saida.txt](casos-teste/12/saida.txt)|
|[13](casos-teste/13)|[D](#árvore-d-três-níveis)|240|Última chave da folha mais à direita|[entrada.txt](casos-teste/13/entrada.txt) [metadados.dat](casos-teste/13/metadados.dat) [clientes.dat](casos-teste/13/clientes.dat) [saida.txt](casos-teste/13/saida.txt)|

### Como compilar e rodar os testes

O projeto tem um Makefile. Abra a pasta do projeto no VSCode e use o terminal integrado (menu Terminal > New Terminal). Os comandos abaixo devem ser executados na pasta do projeto:

|Comando|O que faz|
|---|---|
|`make`|Compila o programa, gerando o executável arvore\_b|
|`make test`|Roda todos os casos de teste e mostra quais passaram e quais falharam|
|`make caso N=4`|Roda apenas o caso 4 e mostra as diferenças entre a sua saída e a saída esperada|
|`make clean`|Apaga o executável e a pasta execucao|

No `make caso`, as linhas marcadas com < são da sua saída e as linhas marcadas com > são da saída esperada. A saída do seu programa fica gravada em execucao/saida\_obtida.txt.

Para usar o make é preciso ter o gcc e o make instalados. No Linux e no macOS eles normalmente já estão disponíveis (no macOS, instale as ferramentas de linha de comando com `xcode-select --install`, se necessário). No Windows, use o WSL ou o MSYS2.

Os comandos `make test` e `make caso` copiam os arquivos .dat do caso para a pasta execucao antes de rodar o programa. Se for rodar o programa manualmente (por exemplo, `./arvore_b` e digitar a chave), copie antes os arquivos .dat do caso para o diretório de execução, senão o programa não vai encontrar a árvore.

## Dicas Importantes:

- A entrada e a saída já são tratadas no arquivo fornecido para ler e imprimir os dados no formato esperado pela questão. Vocês devem APENAS implementar as funções solicitadas no problema
- Os arquivos metadados.c, no.c e cliente.c (e seus respectivos .h) já contêm as funções para ler metadados, nós e clientes. Não é preciso alterá-los. As funções de arvore\_b.c estão declaradas em arvore\_b.h
- Abra o arquivo de dados no modo "rb", pois a busca só precisa ler o arquivo
- Comece a busca pela posição indicada por pont\_raiz no arquivo de metadados. Se pont\_raiz for -1, a árvore está vazia e nenhum nó deve ser lido
- Em cada nó, use a função posicao para descobrir em que posição a chave deveria estar. Se pos for menor que m e a chave da posição pos for a chave buscada, a chave está nesse nó. Caso contrário, a busca continua no filho p[pos] — e, se esse ponteiro for -1, o nó é uma folha e a chave não existe na árvore
- O cliente retornado deve ser uma cópia criada com a função cliente, pois o nó lido do arquivo é liberado com libera\_no ao final da busca
- Leia cada nó do arquivo uma única vez: se o mesmo nó for lido duas vezes, a quantidade de nós lidos vai ficar diferente da esperada
- Na saída, o cliente aparece precedido de um caractere de tabulação, pois é assim que a função imprime\_cliente o imprime
