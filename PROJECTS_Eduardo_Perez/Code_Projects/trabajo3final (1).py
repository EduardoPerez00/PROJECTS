import sqlite3

# Nos conectamos a la base de datos.
conex = sqlite3.connect('mi_base_de_datos_trabajo.db')
curs = conex.cursor()

# Creamos la tabla "Clientes"
curs.execute('''
    CREATE TABLE IF NOT EXISTS Clientes (
        id INTEGER PRIMARY KEY,
        nombre TEXT,
        correo TEXT
    )
''')

# Creamos la tabla "Pedidos"
curs.execute('''
    CREATE TABLE IF NOT EXISTS Pedidos (
        id INTEGER PRIMARY KEY,
        producto TEXT,
        cantidad INTEGER,
        cliente_id INTEGER,
        FOREIGN KEY (cliente_id) REFERENCES Clientes (id)
    )
''')

# Creamos la tabla "Productos"
curs.execute('''
    CREATE TABLE IF NOT EXISTS Productos (
        id INTEGER PRIMARY KEY,
        nombre TEXT,
        precio REAL,
        categoria_id INTEGER,
        FOREIGN KEY (categoria_id) REFERENCES Categorias (id)
    )
''')

# Creamos la tabla "Categorias"
curs.execute('''
    CREATE TABLE IF NOT EXISTS Categorias (
        id INTEGER PRIMARY KEY,
        nombre TEXT
    )
''')

# Insertamos los datos dentro de la tabla "Clientes"
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('Juan', 'juan@example.com'))
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('María', 'maria@example.com'))
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('Pedro', 'pedro@example.com'))
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('Ana', 'ana@example.com'))
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('Carlos', 'carlos@example.com'))
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('Laura', 'laura@example.com'))
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('Roberto', 'roberto@example.com'))
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('Sofía', 'sofia@example.com'))
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('Luis', 'luis@example.com'))
curs.execute("INSERT INTO Clientes (nombre, correo) VALUES (?, ?)", ('Carmen', 'carmen@example.com'))

# Insertamos los datos dentro de la tabla "Pedidos"
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Camisa', 3, 1))
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Pantalón', 2, 2))
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Zapatos', 1, 3))
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Sombrero', 2, 4))
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Vestido', 1, 5))
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Calcetines', 4, 6))
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Chaqueta', 1, 7))
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Bufanda', 2, 8))
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Gorra', 3, 9))
curs.execute("INSERT INTO Pedidos (producto, cantidad, cliente_id) VALUES (?, ?, ?)", ('Bolso', 1, 10))

# Insertamos los datos dentro de la tabla "Productos"
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Camisa', 29.99, 1))
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Pantalón', 49.99, 1))
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Zapatos', 79.99, 2))
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Sombrero', 19.99, 3))
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Vestido', 59.99, 1))
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Calcetines', 9.99, 3))
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Chaqueta', 69.99, 1))
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Bufanda', 14.99, 3))
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Gorra', 24.99, 4))
curs.execute("INSERT INTO Productos (nombre, precio, categoria_id) VALUES (?, ?, ?)", ('Bolso', 39.99, 4))

# Insertamos los datos dentro de la tabla "Categorias"
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Ropa',))
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Ropa',))
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Calzado',))
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Accesorios',))
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Ropa',))
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Accesorios',))
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Ropa',))
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Accesorios',))
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Accesorios',))
curs.execute("INSERT INTO Categorias (nombre) VALUES (?)", ('Bolsos',))

# Modificamos los nombres de los clientes
curs.execute("UPDATE Clientes SET nombre = ? WHERE id = ?", ('Megan', 1))
curs.execute("UPDATE Clientes SET nombre = ? WHERE id = ?", ('Andrew', 2))

# Borramos un par pedidos
curs.execute("DELETE FROM Pedidos WHERE id = ?", (1,))
curs.execute("DELETE FROM Pedidos WHERE id = ?", (3,))

# Realizamos una consulta con JOIN para obtener los datos necesarios
curs.execute('''
    SELECT Clientes.nombre, Pedidos.producto, Productos.precio, Categorias.nombre
    FROM Pedidos
    INNER JOIN Clientes ON Pedidos.cliente_id = Clientes.id
    INNER JOIN Productos ON Pedidos.producto = Productos.nombre
    INNER JOIN Categorias ON Productos.categoria_id = Categorias.id
''')

resultados = curs.fetchall()

print("Consulta:")
for resultado in resultados:
    nombre_cliente = resultado[0]
    producto = resultado[1]
    precio = resultado[2]
    categoria = resultado[3]
    print(f"Cliente: {nombre_cliente}, Producto: {producto}, Precio: {precio}, Categoría: {categoria}")

# Guardamos los cambios realizados
conex.commit()

# Cerramos la conexión con la base
conex.close()
