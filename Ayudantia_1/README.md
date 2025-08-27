# Ayudantía 1 - TEL337 ACO
## Repaso estructuras relevantes

---

## Propósito de cada ejercicio

### 1. [`1-remy.c`](1-remy.c) - Ratón en el laberinto (Backtracking)
**Herramientas que proporciona:**
- **Backtracking puro**: Técnica fundamental para explorar todas las posibilidades
- **Marcado/desmarcado de estados**: `sol[x][y] = 1` para marcar y `sol[x][y] = 0` para desmarcar
- **Validación de límites**: Verificar si estamos dentro del tablero y en casilla válida
- **Propagación de éxito**: Cuando una rama recursiva encuentra solución, se propaga hacia arriba

**Aplicación:** Base para implementar los modos `open`, `closed` y `count`.

### 2. [`2-parque.c`](2-parque.c) - BFS en grafo
**Herramientas que proporciona:**
- **Búsqueda por anchura (BFS)**: Encuentra el camino más corto en grafos no ponderados
- **Cola para BFS**: Estructura de datos necesaria para recorrido nivel por nivel
- **Control de visitados**: Evitar ciclos infinitos
- **Cálculo de distancias**: `dist[v] = dist[u] + 1`

**Aplicación:** Esencial para el modo `shortest` - encontrar el menor número de movimientos.

### 3. [`3-playlist.c`](3-playlist.c) - Lista doblemente enlazada
**Herramientas que proporciona:**
- **Gestión dinámica de memoria**: `malloc()` para crear nodos
- **Estructura de secuencias**: Almacenar la secuencia de movimientos del caballo
- **Navegación bidireccional**: Útil para reconstruir caminos

**Aplicación:** Almacenar y mostrar la secuencia de coordenadas del recorrido.

### 4. [`4-guardaBosque.c`](4-guardaBosque.c) - Árbol binario de búsqueda
**Herramientas que proporciona:**
- **Recursión en estructuras**: Patrón de diseño recursivo
- **Gestión de memoria dinámica**: Crear y manejar estructuras complejas
- **Recorrido sistemático**: Patrón de visita ordenado

**Aplicación:** Refuerza los patrones recursivos necesarios para explorar todas las posibilidades.

---

## Análisis predictivo

### Para `1-remy.c` (Backtracking):

#### Explicación de las estructuras de datos:
```c
static int laberinto[N][N] = {
    {0, 1, 0, 0},  // Fila 0: libre, pared, libre, libre
    {0, 0, 0, 1},  // Fila 1: libre, libre, libre, pared
    {1, 1, 0, 0},  // Fila 2: pared, pared, libre, libre
    {1, 1, 1, 0}   // Fila 3: pared, pared, pared, libre (META)
};

static int sol[N][N] = {0};  // Matriz solución: marca el camino encontrado
```

**Significado de cada valor:**
- **`0`**: Casilla **libre** (se puede caminar)
- **`1`**: **Pared** (no se puede pasar) o **parte del camino** (en matriz `sol`)

**Visualización del laberinto:**
```
Laberinto:          Objetivo sol[]:
 . ■ . .            S . . .
 . . . ■      →     1 1 1 .     
 ■ ■ . .            . . 1 .
 ■ ■ ■ M            . . 1 M

Leyenda: . = libre, ■ = pared, S = inicio, M = meta, 1 = camino
```

#### Variables y lógica del backtracking:
- **`x, y`**: **Coordenadas actuales** en el laberinto
- **`sol[x][y] = 1`**: **Marcar** casilla como parte del camino actual
- **`sol[x][y] = 0`**: **Desmarcar** casilla (backtracking)
- **Condición de éxito**: `x == N-1 && y == N-1` (llegar a la esquina inferior derecha)
- **Movimientos**: Solo hacia **abajo** (`x+1, y`) y **derecha** (`x, y+1`)

#### Flujo del algoritmo:
1. **Verificar si llegamos a la meta** → Si sí, marcar y retornar éxito
2. **Validar casilla actual** → Debe estar en límites, ser libre y no visitada
3. **Marcar casilla** → `sol[x][y] = 1`
4. **Intentar movimientos recursivos** → Abajo o derecha
5. **Si algún movimiento tiene éxito** → Propagar éxito hacia arriba
6. **Si ningún movimiento funciona** → Desmarcar casilla (backtrack)

**P1:** ¿Qué pasará si ejecutamos el programa con el laberinto actual? ¿Encontrará un camino?
<details>
<summary>Ver respuesta</summary>
<b>R1:</b> Sí, encontrará un camino. El laberinto permite ir de (0,0) a (3,3) siguiendo: (0,0)→(1,0)→(1,1)→(1,2)→(2,2)→(3,3).
</details>

**P2:** En la línea `if (mover(x+1, y) || mover(x, y+1)) return 1;`, ¿qué sucede si la primera llamada `mover(x+1, y)` retorna 1?
<details>
<summary> Ver respuesta</summary>
<b>R2:</b> Se ejecuta el <code>return 1</code> inmediatamente debido al operador <code>||</code> (cortocircuito), sin evaluar <code>mover(x, y+1)</code>.
</details>

**P3:** ¿Por qué es crucial la línea `sol[x][y] = 0;` después de las llamadas recursivas?
<details>
<summary> Ver respuesta</summary>
<b>R3:</b> Porque desmarca la casilla para que pueda ser usada en otros caminos alternativos. Sin esto, el backtracking no funcionaría correctamente.
</details>

**P4:** Si cambiamos `laberinto[1][1] = 1;`, ¿qué ocurrirá?
<details>
<summary> Ver respuesta</summary>
<b>R4:</b> El programa reportará "No hay camino posible" porque se bloquea una casilla crítica en el único camino viable.
</details>

**P4.1:** ¿Cuál será exactamente la salida del programa si encuentra solución?
<details>
<summary> Ver respuesta</summary>
<b>R4.1:</b>
<pre>
Camino encontrado (1 = camino):
1 0 0 0 
1 1 1 0 
0 0 1 0 
0 0 1 1 
</pre>
</details>

### Para `2-parque.c` (BFS):

#### Explicación de la matriz de adyacencia:
```c
int grafo[N][N] = {
    {0,1,1,0,0,0},  // Atracción 0 conectada con: 1, 2
    {1,0,0,1,0,0},  // Atracción 1 conectada con: 0, 3
    {1,0,0,1,1,0},  // Atracción 2 conectada con: 0, 3, 4
    {0,1,1,0,0,1},  // Atracción 3 conectada con: 1, 2, 5
    {0,0,1,0,0,1},  // Atracción 4 conectada con: 2, 5
    {0,0,0,1,1,0}   // Atracción 5 conectada con: 3, 4
};
```

**Significado de cada valor:**
- **`1`**: Existe una **conexión directa** entre dos atracciones del parque
- **`0`**: **NO existe conexión directa** entre dos atracciones

**Visualización del grafo:**
```
     0 ——— 1 ——— 3
     |           |
     |           |  
     2 ——— 4 ——— 5
```

#### Variables importantes en BFS:
- **`s`**: **Nodo de inicio** (starting node) - En `main()` se usa `BFS(0)`
- **`vis[N]`**: **Visited** - controla qué nodos ya visitamos
  - `vis[i] = 0` → Atracción `i` NO visitada
  - `vis[i] = 1` → Atracción `i` YA visitada
- **`dist[N]`**: **Distance** - distancia mínima desde el nodo inicial
  - `dist[i]` = número mínimo de "saltos" para llegar desde `s` hasta `i`
- **`q`**: **Queue** - cola FIFO para procesar nodos por niveles
  - `q.f` → Frente de la cola (primer elemento)
  - `q.r` → Rear de la cola (último elemento)

**P5:** ¿En qué orden visitará BFS los nodos desde el nodo 0?
<details>
<summary> Ver respuesta</summary>
<b>R5:</b> 0 → 1,2 → 3 → 4,5 (nivel por nivel, según las conexiones del grafo).
</details>

**P6:** ¿Qué representa exactamente `dist[v] = dist[u] + 1;`?
<details>
<summary> Ver respuesta</summary>
<b>R6:</b> La distancia mínima (en número de aristas) desde el nodo inicial hasta el nodo <code>v</code>.
</details>

**P7:** ¿Por qué BFS garantiza encontrar el camino más corto?
<details>
<summary> Ver respuesta</summary>
<b>R7:</b> Porque explora todos los nodos a distancia <code>k</code> antes de explorar nodos a distancia <code>k+1</code>.
</details>

**P7.1:** ¿Cuál será el resultado final de ejecutar `BFS(0)`?
<details>
<summary> Ver respuesta</summary>
<b>R7.1:</b> 
<pre>
Atracción 0 a distancia 0  (punto de inicio)
Atracción 1 a distancia 1  (1 salto: 0→1)
Atracción 2 a distancia 1  (1 salto: 0→2)
Atracción 3 a distancia 2  (2 saltos: 0→1→3 o 0→2→3)
Atracción 4 a distancia 2  (2 saltos: 0→2→4)
Atracción 5 a distancia 3  (3 saltos: 0→2→4→5)
</pre>
</details>

### Para `3-playlist.c` (Lista enlazada):

#### Explicación de la estructura del nodo:
```c
typedef struct Nodo {
    char cancion[30];        // Nombre de la canción (hasta 29 caracteres + \0)
    struct Nodo *sig, *ant;  // Punteros al siguiente y anterior nodo
} Nodo;
```

**Componentes de cada nodo:**
- **`cancion[30]`**: Array de caracteres para almacenar el nombre
- **`*sig`**: Puntero al **siguiente** nodo (hacia adelante)
- **`*ant`**: Puntero al nodo **anterior** (hacia atrás)

#### Funcionamiento de la inserción:
```c
void insertar(Nodo **head, char *nombre){
    Nodo* n=malloc(sizeof(Nodo));  // 1. Crear nuevo nodo
    strcpy(n->cancion,nombre);     // 2. Copiar nombre de canción
    n->sig=*head;                  // 3. El nuevo nodo apunta al actual primero
    n->ant=NULL;                   // 4. El nuevo nodo es el primero (no tiene anterior)
    if(*head) (*head)->ant=n;      // 5. Si hay lista, conectar hacia atrás
    *head=n;                       // 6. El nuevo nodo se convierte en cabeza
}
```

**Visualización paso a paso:**
```
Inicial: lista = NULL

Después de insertar("Song C"):
[Song C] → NULL

Después de insertar("Song B"):
[Song B] ⇄ [Song C] → NULL

Después de insertar("Song A"):
[Song A] ⇄ [Song B] ⇄ [Song C] → NULL
```

#### Variables importantes:
- **`**head`**: Puntero al puntero de la cabeza (permite modificar la cabeza)
- **`*nombre`**: Puntero al string con el nombre de la canción
- **`*cur`**: Cursor para recorrer la lista desde el inicio

#### Lógica del recorrido:
```c
void recorrer(Nodo *cur){
    while(cur){                    // Mientras no sea NULL
        printf("▶ %s\n", cur->cancion);  // Imprimir canción actual
        cur=cur->sig;              // Avanzar al siguiente nodo
    }
}
```

**P8:** ¿En qué orden se imprimirán las canciones?
<details>
<summary> Ver respuesta</summary>
<b>R8:</b> "Song A", "Song B", "Song C" (porque cada inserción es al inicio de la lista).
</details>

**P9:** ¿Qué ventaja tiene usar una lista doblemente enlazada versus una simple?
<details>
<summary> Ver respuesta</summary>
<b>R9:</b> Permite navegación en ambas direcciones, útil para reconstruir caminos o hacer recorridos bidireccionales.
</details>

**P9.1:** ¿Cuál será exactamente la salida del programa?
<details>
<summary> Ver respuesta</summary>
<b>R9.1:</b>
<pre>
▶ Song A
▶ Song B
▶ Song C
</pre>
</details>

**P9.2:** ¿Qué pasaría si quisiéramos recorrer la lista en orden inverso desde el último nodo?
<details>
<summary> Ver respuesta</summary>
<b>R9.2:</b> Podríamos usar <code>cur = cur->ant</code> en lugar de <code>cur = cur->sig</code> para ir hacia atrás, pero necesitaríamos primero llegar al último nodo.
</details>

### Para `4-guardaBosque.c` (Árbol BST):

#### Explicación de la estructura del nodo:
```c
typedef struct Nodo {
    int val;                    // Valor almacenado en el nodo
    struct Nodo *izq, *der;     // Punteros a hijos izquierdo y derecho
} Nodo;
```

**Propiedad del BST (Binary Search Tree):**
- **Hijo izquierdo**: Todos los valores **menores** que el nodo actual
- **Hijo derecho**: Todos los valores **mayores o iguales** que el nodo actual

#### Funcionamiento de la inserción recursiva:
```c
Nodo* insertar(Nodo* r,int v){
    if(!r) return nuevo(v);           // Caso base: crear nuevo nodo
    if(v < r->val) r->izq=insertar(r->izq,v);  // Insertar a la izquierda
    else r->der=insertar(r->der,v);            // Insertar a la derecha
    return r;                         // Retornar la raíz (sin cambios)
}
```

#### Construcción paso a paso del árbol:
```
Secuencia de inserción: 5, 2, 8, 1, 3

Paso 1: insertar(5)     Paso 2: insertar(2)     Paso 3: insertar(8)
       [5]                    [5]                      [5]
                             /                        /   \
                           [2]                      [2]   [8]

Paso 4: insertar(1)     Paso 5: insertar(3)
       [5]                    [5]
      /   \                  /   \
    [2]   [8]              [2]   [8]
   /                      /  \
 [1]                    [1]  [3]
```

#### Recorrido Inorder (izquierda → raíz → derecha):
```c
void inorder(Nodo* r){
    if(r){                    // Si el nodo existe
        inorder(r->izq);      // 1. Recorrer subárbol izquierdo
        printf("%d ",r->val); // 2. Imprimir valor del nodo actual
        inorder(r->der);      // 3. Recorrer subárbol derecho
    }
}
```

**Orden de visita para nuestro árbol:**
```
inorder([1]) → imprime "1"
inorder([2]) → imprime "2"  
inorder([3]) → imprime "3"
inorder([5]) → imprime "5"
inorder([8]) → imprime "8"
```

#### Variables importantes:
- **`r`**: Puntero a la **raíz** del (sub)árbol actual
- **`v`**: **Valor** a insertar
- **`raiz`**: Puntero a la raíz del árbol completo

**P10:** ¿En qué orden imprimirá los valores el recorrido `inorder`?
<details>
<summary> Ver respuesta</summary>
<b>R10:</b> 1, 2, 3, 5, 8 (orden ascendente, propiedad del recorrido inorder en BST).
</details>

**P11:** ¿Qué sucede si insertamos el valor 4 en el árbol?
<details>
<summary> Ver respuesta</summary>
<b>R11:</b> Se insertará como hijo derecho del nodo 3, manteniendo la propiedad del BST.
</details>

**P11.1:** ¿Cuál será exactamente la salida del programa?
<details>
<summary> Ver respuesta</summary>
<b>R11.1:</b> <code>1 2 3 5 8</code> (números separados por espacios, sin salto de línea final).
</details>

**P11.2:** ¿Por qué el recorrido inorder en un BST siempre produce una secuencia ordenada?
<details>
<summary> Ver respuesta</summary>
<b>R11.2:</b> Porque primero visita todos los valores menores (subárbol izquierdo), luego el nodo actual, y finalmente todos los valores mayores (subárbol derecho).
</details>

**P11.3:** Si insertáramos los valores en diferente orden (ej: 1,2,3,5,8), ¿cómo sería el árbol?
<details>
<summary> Ver respuesta</summary>
<b>R11.3:</b> Sería completamente desbalanceado (una "lista" hacia la derecha), pero el recorrido inorder seguiría dando el mismo resultado ordenado.
</details>

### Preguntas integradoras para otros problemas similares:

**P12:** ¿Cómo combinarías backtracking (del ratón) con BFS para resolver el problema del caballo?
<details>
<summary> Ver respuesta</summary>
<b>R12:</b> Backtracking para los recorridos completos (<code>open</code>, <code>closed</code>, <code>count</code>) y BFS para el camino más corto (<code>shortest</code>).
</details>

**P13:** ¿Cuál sería la principal diferencia entre el modo `open` y `closed` del caballo?
<details>
<summary> Ver respuesta</summary>
<b>R13:</b> En <code>closed</code>, además de visitar todas las casillas, la posición final debe estar a un movimiento de caballo de la posición inicial.
</details>

**P14:** ¿Por qué el modo `count` sería computacionalmente más costoso que `open`?
<details>
<summary> Ver respuesta</summary>
<b>R14:</b> Porque <code>count</code> debe explorar TODAS las soluciones posibles sin detenerse en la primera, mientras que <code>open</code> se detiene al encontrar una solución.
</details>