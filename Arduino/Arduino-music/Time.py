# Diccionario para duraciones predefinidas según la cantidad de guiones
durations_map = {
    0: 8,   # Corchea (ningún guion)
    1: 8,   # Corchea (un guion)
    2: 4,   # Negra (dos guiones)
    3: 4,   # Negra (tres guiones)
    4: 2,   # Blanca (cuatro guiones o más)
}

# Función para calcular las duraciones basadas en los guiones
def parse_durations(sequence):
    durations = []
    
    # Separar mano/octava de las notas
    lines = sequence.strip().split('|')
    notes = lines[1].strip()  # Extraer solo la parte de las notas
    
    current_duration = 0  # Inicia con duración 0 para acumular si hay '-'
    
    # Recorrer las notas y símbolos en la secuencia
    for char in notes:
        # Si es una nota, agregamos la duración basada en los guiones anteriores
        if char.isalpha():
            duration = durations_map.get(current_duration, 8)  # Si no está, es una corchea
            durations.append(duration)
            current_duration = 0  # Reiniciar el contador de guiones
        elif char == '-':
            # Incrementar la duración por cada guion
            current_duration += 1

    return durations

# Procesar la secuencia de entrada

input_sequence = input("Introduce la secuencia de entrada (ejemplo: RH:5|f-e-f-g-d-----f-g-a---f-g-|): ")
durations = parse_durations(input_sequence)

# Mostrar los resultados
print("Note durations (rítmicas):", durations)
