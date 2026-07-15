class Matrix:
    def __init__(self , data):
        self.data = data
        self.rows = len(data)
        self.cols = len(data[0])
    
    def __add__(self, other):
        result = []
        for i in range(self.rows):
            curr_row = []
            for j in range(self.cols):
                sum_val = self.data[i][j] + other.data[i][j]
                curr_row.append(sum_val)
            result.append(curr_row)
        return Matrix(result)
    
    def __sub__(self, other):
        result = []
        for i in range(self.rows):
            curr_row = []
            for j in range(self.cols):
                sum_val = self.data[i][j] - other.data[i][j]
                curr_row.append(sum_val)
            result.append(curr_row)
        return Matrix(result)
    
    def __mul__(self, other):
        if self.cols != other.rows :
            raise ValueError("Cannot Multiply")
        result = []
        for i in range(self.rows):
            curr_row = []
            for j in range(other.cols):
                dot_pro = 0
                for k in range(self.cols):
                    dot_pro += self.data[i][k] * other.data[k][j]
                curr_row.append(dot_pro)
            result.append(curr_row)
        return Matrix(result)

A = Matrix([[1,2]])
B = Matrix([[5,6],[7,8]])
C = A * B
print(C.data)