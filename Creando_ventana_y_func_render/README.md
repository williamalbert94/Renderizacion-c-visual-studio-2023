# Renderizacion c++ usando visual studio

## 1.) creando una ventana y nuestra funcion inicial de renderizacion

inicialmente la idea es crear una funcion, que nos permita tener una imagen(array de 3 dimensiones w,h,c llamado filme)
La funcion nos ayudara a crear un cavnas, a hacer un set value en la imagen, a retornar valores en la imagen, 
retornar coordenadas y actualizar lo que se vera en el cavnas en SDL.

Como salida en este paso deberiamos tener algo asi:

<h3 align="center">
  <img src="../imagenes/ventana_inicial.png" width="900">
</h3>

```

Nuestra funcion objetivo Render en pseudocodigo sera:
//
funcion render_raytracing_phong(escena):
    para cada pixel en la imagen:
        crear un rayo que pase por el pixel
        intersectar el rayo con los objetos en la escena
        si hay intersección:
            encontrar el punto de intersección más cercano
            calcular la iluminación en el punto utilizando el modelo de Phong:
                - calcular la componente difusa
                - calcular la componente especular
                - sumar ambas componentes
            guardar el color resultante en el pixel
        sino:
            asignar un color de fondo al pixel
    mostrar la imagen renderizada

```

Ref: "Computer Graphics: Principles and Practice", tercera edición, escrito por James D. Foley, Andries van Dam, Steven K. Feiner y John F. Hughes. 

En el capítulo 16 de este libro se explica el modelo de iluminación de Phong y se muestra cómo se puede utilizar en un algoritmo de raytracing.


