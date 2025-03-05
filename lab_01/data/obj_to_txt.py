def parse_obj(file_path):
    points = []
    edges = []
    with open(file_path, 'r') as f:
        for line in f:
            # Чтение точек
            if line.startswith('v '):
                # Формат точки: v x y z
                parts = line.split()
                x, y, z = map(float, parts[1:])
                points.append((x, y, z))
            
            # Чтение граней
            elif line.startswith('f '):
                # Формат грани: f 1 2 3
                parts = line.split()
                # Убираем символы (например, текст в случае многоугольников) и оставляем только индексы
                indices = [int(p.split('/')[0]) - 1 for p in parts[1:]]  # индексы начинаются с 1, поэтому -1
                # Для треугольных граней, создаем отрезки
                for i in range(len(indices)):
                    edges.append((indices[i], indices[(i + 1) % len(indices)]))
    
    return points, edges


def write_to_custom_format(points, edges, output_path):
    with open(output_path, 'w') as f:
        # Запись количества точек
        f.write(f"{len(points)}\n")
        
        # Запись координат точек
        for point in points:
            f.write(f"{point[0]} {point[1]} {point[2]}\n")
        
        # Запись количества отрезков
        f.write(f"{len(edges)}\n")
        
        # Запись отрезков
        for edge in edges:
            f.write(f"{edge[0]} {edge[1]} \n")


def main(input_obj_path, output_txt_path):
    points, edges = parse_obj(input_obj_path)
    write_to_custom_format(points, edges, output_txt_path)


if __name__ == '__main__':
    input_obj_path = input("Путь к .obj файлу: ")
    output_txt_path = input("Название итогового файла: ")
    
    main(input_obj_path, output_txt_path)