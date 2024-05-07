# problema-da-mochila
 problema de otimização classico
Evento Beneficente B (Problema da Mochila)

projeto desenvolvido na disciplina de LINGUAGENS DE PROGRAMAÇÃO 1 - CIENCIA DA COMPUTAÇÃO
Universidade Federal do Maranhão

professor: Glaubos

autores: Guilherme Barrio Nascimento , Filipe , Hyago aguiar

1 - Pré-requisitos
Compilador C/C++ (gcc) instalado na máquina.

2 - Instalação
Descompactar o arquivo Trabalhofinal.zip em um diretório, seram copiados para este diretório os seguintes arquivos:

	1 - trabalho_LP_final.c: que contem o codigo fonte.
	2 - makefile.bat: arquivo em lote para compilar o codigo fonte.
	3 - input.txt: contem os dados de input.

Todos os arquivos devem estar no mesmo diretório.
Para gerar outros arquivios de entrada, siga as instruções informadas na sessão 5.

3 - Compilação e Execução
Executar o arquivo makefile da seguinte forma: makefile  trabalho_LP_final.c  .
Será gerado o arquivo binário  trabalho_LP_final.exe que irá ser executado automaticamente após a compilação.

4 - Descrição do projeto
Imagine que você é o organizador de um evento beneficente e possui um caminhão com capacidade de carga limitada para transportar donativos. 
Você tem diversos tipos de itens para enviar, como alimentos, roupas e brinquedos, cada um com seu respectivo peso e valor para a comunidade que irá recebê-los.
Seu desafio é determinar qual combinação de itens maximiza o valor total dos donativos enviados, sem exceder a capacidade do caminhão. 
Ou você envia o item completo, ou não envia. Não é possível enviar uma "parte" do item.

5 - Funcionalidades do projeto
O programa irá solicitar o nome do arquivo de entrada que contem o número total de itens, peso máximo e valores e pesos de cada item.
Será gerado o arquvio resultados.txt contendo a solução do problema da machila para os dados informados no arquivo input.txt.
O formato dos arquivos de entrada e saída são informados nas próximas seções.
 
5.1 Formato de Input
O arquivo de input deve conter apenas números (inteiros ou de ponto flutuante), sendo os dois primeiros o numero de itens de seleção, e a capacidade máxima do caminhão, respectivamente.
As entradas seguintes devem ser os valores e pesos dos itens, tendo cada item apenas uma entrada, seguindo a ordem valorN pesoN.
Os arquivos de entrada de dados deve ter o seguinte formato:

n      cap_max
valor1 peso1
valor2 peso2
...
valorN pesoN

onde,
n: numero de itens.
cap_max: capacidade máxima do caminhão.
valorN: valor do donativo para a comunidade.
pesoN: peso do donativo para o caminhão.

5.2 - Formato do Output
O arquivo de output contém os itens selecionados, na ordem de input, com seu respectivo valor e peso, além de apresentar a soma total dos valores.

6 - Lógica do Programa
  I. Estruturas de Dados: O código define "itens_mochila" e "parametros_problema" para armazenar informações sobre os itens e as restrições do problema.

  II. Funções de Leitura: "leitura_elementos" e "leitura_parametro_geral" são usadas para ler dados do arquivo.

  III. Algoritmo da Mochila: A função "mochila" resolve o problema da mochila usando programação dinâmica. 
       Ela determina a combinação de itens mais valiosa que a mochila pode carregar.

     III-1. Inicialização: Inicializa uma matriz "matriz[quantidade + 1][peso_max + 1]" para armazenar os valores máximos que podem ser obtidos com um determinado número 
            de itens e capacidade de peso.
   
     III-2. Preenchimento da Matriz: Preenche a matriz considerando se incluir ou não cada item na mochila.
   
     III-3. Rastreamento da Solução: Rastreia a solução a partir da célula "matriz[quantidade][peso_max]" para determinar quais itens foram incluídos na mochila.

  IV. Função Principal: A função "main" lê os dados do arquivo e chama a função "mochila" para resolver o problema. A solução é impressa na tela.

 Em resumo, o código lê os dados do problema, resolve o problema da mochila e imprime a solução. 
 A solução é obtida usando programação dinâmica, que divide o problema em subproblemas menores, resolve esses subproblemas e usa suas soluções para resolver o problema 
 original.