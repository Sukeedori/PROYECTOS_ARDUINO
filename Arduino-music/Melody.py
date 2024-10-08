# Mapa de notas a constantes de pitches.h
note_map = {
    # Octava 1
    'C1': 'NOTE_C1', 'CS1': 'NOTE_CS1', 'D1': 'NOTE_D1', 'DS1': 'NOTE_DS1',
    'E1': 'NOTE_E1', 'F1': 'NOTE_F1', 'FS1': 'NOTE_FS1', 'G1': 'NOTE_G1', 
    'GS1': 'NOTE_GS1', 'A1': 'NOTE_A1', 'AS1': 'NOTE_AS1', 'B1': 'NOTE_B1',

    # Octava 2
    'C2': 'NOTE_C2', 'CS2': 'NOTE_CS2', 'D2': 'NOTE_D2', 'DS2': 'NOTE_DS2',
    'E2': 'NOTE_E2', 'F2': 'NOTE_F2', 'FS2': 'NOTE_FS2', 'G2': 'NOTE_G2', 
    'GS2': 'NOTE_GS2', 'A2': 'NOTE_A2', 'AS2': 'NOTE_AS2', 'B2': 'NOTE_B2',

    # Octava 3
    'C3': 'NOTE_C3', 'CS3': 'NOTE_CS3', 'D3': 'NOTE_D3', 'DS3': 'NOTE_DS3',
    'E3': 'NOTE_E3', 'F3': 'NOTE_F3', 'FS3': 'NOTE_FS3', 'G3': 'NOTE_G3', 
    'GS3': 'NOTE_GS3', 'A3': 'NOTE_A3', 'AS3': 'NOTE_AS3', 'B3': 'NOTE_B3',

    # Octava 4
    'C4': 'NOTE_C4', 'CS4': 'NOTE_CS4', 'D4': 'NOTE_D4', 'DS4': 'NOTE_DS4',
    'E4': 'NOTE_E4', 'F4': 'NOTE_F4', 'FS4': 'NOTE_FS4', 'G4': 'NOTE_G4', 
    'GS4': 'NOTE_GS4', 'A4': 'NOTE_A4', 'AS4': 'NOTE_AS4', 'B4': 'NOTE_B4',

    # Octava 5
    'C5': 'NOTE_C5', 'CS5': 'NOTE_CS5', 'D5': 'NOTE_D5', 'DS5': 'NOTE_DS5',
    'E5': 'NOTE_E5', 'F5': 'NOTE_F5', 'FS5': 'NOTE_FS5', 'G5': 'NOTE_G5', 
    'GS5': 'NOTE_GS5', 'A5': 'NOTE_A5', 'AS5': 'NOTE_AS5', 'B5': 'NOTE_B5',

    # Octava 6
    'C6': 'NOTE_C6', 'CS6': 'NOTE_CS6', 'D6': 'NOTE_D6', 'DS6': 'NOTE_DS6',
    'E6': 'NOTE_E6', 'F6': 'NOTE_F6', 'FS6': 'NOTE_FS6', 'G6': 'NOTE_G6', 
    'GS6': 'NOTE_GS6', 'A6': 'NOTE_A6', 'AS6': 'NOTE_AS6', 'B6': 'NOTE_B6',

    # Octava 7
    'C7': 'NOTE_C7', 'CS7': 'NOTE_CS7', 'D7': 'NOTE_D7', 'DS7': 'NOTE_DS7',
    'E7': 'NOTE_E7', 'F7': 'NOTE_F7', 'FS7': 'NOTE_FS7', 'G7': 'NOTE_G7', 
    'GS7': 'NOTE_GS7', 'A7': 'NOTE_A7', 'AS7': 'NOTE_AS7', 'B7': 'NOTE_B7',

    # Octava 8
    'C8': 'NOTE_C8', 'CS8': 'NOTE_CS8', 'D8': 'NOTE_D8', 'DS8': 'NOTE_DS8'
}
# Función para convertir las notas en formato adecuado
def parse_sequence(sequence):
    melody = []
    
    # Separar mano/octava de las notas
    lines = sequence.strip().split('|')
    hand, octave = lines[0].split(':')  # Obtener la octava desde la secuencia
    notes = lines[1].strip()
    
    # Recorrer las notas y símbolos en la secuencia
    for char in notes:
        # Si es una nota, agregamos la nota
        if char.isalpha():
            note_key = char.upper() + octave  # Convertir la nota en su constante, ej. 'f' -> 'F5'
            if note_key in note_map:
                melody.append(note_map[note_key])  # Agregar la constante a la lista de melodía
                
    return melody

# Pedir al usuario que ingrese la secuencia de entrada
input_sequence = input("Introduce la secuencia de entrada (ejemplo: RH:5|f-e-f-g-d-----f-g-a---f-g-|): ")

# Llamar a la función y obtener la lista de melodías
melody = parse_sequence(input_sequence)

# Mostrar los resultados como una cadena sin comillas, separada por comas
print("Melody (constants):", ', '.join(melody))