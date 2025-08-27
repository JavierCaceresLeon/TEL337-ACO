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

**Aplicación al Caballo:** Base para implementar los modos `open`, `closed` y `count`.

### 2. [`2-parque.c`](2-parque.c) - BFS en grafo
**Herramientas que proporciona:**
- **Búsqueda por anchura (BFS)**: Encuentra el camino más corto en grafos no ponderados
- **Cola para BFS**: Estructura de datos necesaria para recorrido nivel por nivel
- **Control de visitados**: Evitar ciclos infinitos
- **Cálculo de distancias**: `dist[v] = dist[u] + 1`

**Aplicación al Caballo:** Esencial para el modo `shortest` - encontrar el menor número de movimientos.

### 3. [`3-playlist.c`](3-playlist.c) - Lista doblemente enlazada
**Herramientas que proporciona:**
- **Gestión dinámica de memoria**: `malloc()` para crear nodos
- **Estructura de secuencias**: Almacenar la secuencia de movimientos del caballo
- **Navegación bidireccional**: Útil para reconstruir caminos

**Aplicación al Caballo:** Almacenar y mostrar la secuencia de coordenadas del recorrido.

### 4. [`4-guardaBosques.c`](4-guardaBosques.c) - Árbol binario de búsqueda
**Herramientas que proporciona:**
- **Recursión en estructuras**: Patrón de diseño recursivo
- **Gestión de memoria dinámica**: Crear y manejar estructuras complejas
- **Recorrido sistemático**: Patrón de visita ordenado

**Aplicación al Caballo:** Refuerza los patrones recursivos necesarios para explorar todas las posibilidades.

---

## Análisis predictivo

### Para `1-remy.c` (Backtracking):

**P1:** ¿Qué pasará si ejecutamos el programa con el laberinto actual? ¿Encontrará un camino?
<details>
<summary>Ver respuesta</summary>
<b>R1:</b> Sí, encontrará un camino. El laberinto permite ir de (0,0) a (3,3) moviéndose solo hacia abajo y derecha.
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

### Para `2-parque.c` (BFS):

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

### Para `3-playlist.c` (Lista enlazada):

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

### Para `4-guardaBosques.c` (Árbol BST):

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

### Preguntas integradoras para el problema del Caballo:

**P12:** ¿Cómo combinarías backtracking (del ratón) con BFS para resolver el problema del caballo?
<details>
<summary> Ver respuesta</summary>
<b>R12:</b> Backtracking para los recorridos completos (<code>open</code>, <code>closed</code>, <code>count</code>) y BFS para el camino más corto (<code>shortest</code>).
</details>

**P13:** ¿Cuál sería la principal diferencia entre el modo `open` y `closed` del caballo?
<details>
<summary>👁️ Ver respuesta</summary>
<b>R13:</b> En <code>closed</code>, además de visitar todas las casillas, la posición final debe estar a un movimiento de caballo de la posición inicial.
</details>

**P14:** ¿Por qué el modo `count` sería computacionalmente más costoso que `open`?
<details>
<summary> Ver respuesta</summary>
<b>R14:</b> Porque <code>count</code> debe explorar TODAS las soluciones posibles sin detenerse en la primera, mientras que <code>open</code> se detiene al encontrar una solución.
</details>