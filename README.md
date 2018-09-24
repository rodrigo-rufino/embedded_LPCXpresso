# embedded_LPCXpresso
Project using LPC1769

| Componente      | Completo |
|-----------------|---|
| Led             | x |
| Acc             | x |
| Temp            | x |
| Joystick        | x |
| Botão           | x |
| Web             |   |

## Led RGB
O Led RGB é responsável por mostrar na placa os dados obtidos pelos sensores.

## Acelerômetro
O acelerômetro é responsável por detectar inclinação na placa. 
* Se ela estiver na horizontal (eixo Z com maior valor), o Led ficará vermelho.
* Se ela estiver inclinada para direita ou esquerda (eixo X com maior valor), o Led ficará azul. 
* Se ela estiver inclunada para cima ou para baixo (eixo Y com maior valor), o Led ficará verde.

## Joystick
O joystick é responsável por simular um sensor de nível.
* Se o nível for menor que 3, o Led ficará vermelho.
* Se o nível estiver entre 3 e 7, o Led ficará azul.
* Se o nível for maior ou igual a 7, o Led ficará verde.

## Temperatura
O sensor de temperatura é responsável por medir a temperatura ambiente.
* Se a temperatura for menor que 20ºC, o Led ficará azul.
* Se a temperatura estiver entre 20 e 30ºC, o Led ficará verde.
* Se a temperatura for maior ou igual a 30ºC, o Led ficará vermelho.

## Botão
O botão é responsável por selecionar qual sensor será lido.
* 0 = Sensor de nível (joystick)
* 1 = Acelerômetro
* 2 = Temperatura

## WEB
Em progresso...


## Adicionais
### Barra de Leds
A barra de Leds ficará se movimentando quando o acelerômetro estiver selecionado.
### Display OLED
O display OLED mostrará as informações capturadas pelos sensores.