# Correcciones realizadas:

 - [BST](#bst)
     - [Visit](#visit)
       
## BST:

### Visit:
Se modificó la función `inOrder()`. Antes el manejo para corroborar si era el primer nodo era hecho con `.tellp()`, sin embargo, debido a que podría llegar a fallar ya que trabaja con las posiciones de la memoria, se decidió mejor que para cualquier nodo se le ponga el espacio antes y posteriormente se elimine dicho espacio.
