# Mapa de notas a constantes de pitches.h
note_map = {
    # Octava 5
    'C5': 'NOTE_C5', 'CS5': 'NOTE_CS5', 'D5': 'NOTE_D5', 'DS5': 'NOTE_DS5',
    'E5': 'NOTE_E5', 'F5': 'NOTE_F5', 'FS5': 'NOTE_FS5', 'G5': 'NOTE_G5',
    'GS5': 'NOTE_GS5', 'A5': 'NOTE_A5', 'AS5': 'NOTE_AS5', 'B5': 'NOTE_B5',
    
    # Octava 4
    'C4': 'NOTE_C4', 'CS4': 'NOTE_CS4', 'D4': 'NOTE_D4', 'DS4': 'NOTE_DS4',
    'E4': 'NOTE_E4', 'F4': 'NOTE_F4', 'FS4': 'NOTE_FS4', 'G4': 'NOTE_G4',
    'GS4': 'NOTE_GS4', 'A4': 'NOTE_A4', 'AS4': 'NOTE_AS4', 'B4': 'NOTE_B4',
    
    # Octava 3
    'C3': 'NOTE_C3', 'CS3': 'NOTE_CS3', 'D3': 'NOTE_D3', 'DS3': 'NOTE_DS3',
    'E3': 'NOTE_E3', 'F3': 'NOTE_F3', 'FS3': 'NOTE_FS3', 'G3': 'NOTE_G3',
    'GS3': 'NOTE_GS3', 'A3': 'NOTE_A3', 'AS3': 'NOTE_AS3', 'B3': 'NOTE_B3'
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

# Secuencias de entrada
sequences = [
    "RH:5|f-e-f-g-d-----f-g-a---f-g-|",
    "RH:5|--------a-----------------|",
    "LH:4|----------d-f-------d---c-|",
    "LH:3|--------A---------A-------|"
]

# Procesar todas las secuencias
for seq in sequences:
    melody = parse_sequence(seq)
    # Convertir la lista de melody a una cadena con elementos separados por comas
    melody_str = ', '.join(melody)
    print(f"Melody (constants) for {seq}: {melody_str}")
