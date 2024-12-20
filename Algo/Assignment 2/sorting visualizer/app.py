from flask import Flask, render_template, request, jsonify

app = Flask(__name__)

# Bubble Sort
def bubble_sort(arr):
    steps = []
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
            steps.append(arr.copy())
    return steps

# Selection Sort
def selection_sort(arr):
    steps = []
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
        steps.append(arr.copy())
    return steps

# Insertion Sort
def insertion_sort(arr):
    steps = []
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
        steps.append(arr.copy())
    return steps

# Merge Sort
def merge_sort(arr):
    steps = []
    def merge_sort_helper(arr):
        if len(arr) > 1:
            mid = len(arr) // 2
            left_half = arr[:mid]
            right_half = arr[mid:]

            merge_sort_helper(left_half)
            merge_sort_helper(right_half)

            i = j = k = 0
            while i < len(left_half) and j < len(right_half):
                steps.append(arr.copy())
                if left_half[i] < right_half[j]:
                    arr[k] = left_half[i]
                    i += 1
                else:
                    arr[k] = right_half[j]
                    j += 1
                k += 1

            while i < len(left_half):
                arr[k] = left_half[i]
                i += 1
                k += 1

            while j < len(right_half):
                arr[k] = right_half[j]
                j += 1
                k += 1
            steps.append(arr.copy())

    merge_sort_helper(arr)
    return steps

# Heap Sort
def heapify(arr, n, i, steps):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left < n and arr[left] > arr[largest]:
        largest = left

    if right < n and arr[right] > arr[largest]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        steps.append(arr.copy())
        heapify(arr, n, largest, steps)

def heap_sort(arr):
    steps = []
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i, steps)

    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        steps.append(arr.copy())
        heapify(arr, i, 0, steps)

    return steps

# Quick Sort
def quick_sort(arr):
    steps = []
    def quick_sort_helper(arr):
        if len(arr) <= 1:
            return arr
        pivot = arr[len(arr) // 2]
        left = [x for x in arr if x < pivot]
        middle = [x for x in arr if x == pivot]
        right = [x for x in arr if x > pivot]
        result = quick_sort_helper(left) + middle + quick_sort_helper(right)
        steps.append(result)
        return result
    quick_sort_helper(arr)
    return steps

# Counting Sort
def counting_sort(arr):
    steps = []
    max_val = max(arr)
    count = [0] * (max_val + 1)

    for num in arr:
        count[num] += 1

    index = 0
    for num, cnt in enumerate(count):
        for _ in range(cnt):
            arr[index] = num
            steps.append(arr.copy())
            index += 1

    return steps

# Bucket Sort
def bucket_sort(arr):
    steps = []
    max_val = max(arr)
    bucket_count = len(arr)
    buckets = [[] for _ in range(bucket_count)]

    for num in arr:
        index = int(num * bucket_count / (max_val + 1))
        buckets[index].append(num)

    for i in range(bucket_count):
        buckets[i] = sorted(buckets[i])
        for num in buckets[i]:
            arr.append(num)
            steps.append(arr.copy())

    return steps

# Radix Sort
def get_digit(num, digit):
    return (num // (10 ** digit)) % 10

def radix_sort(arr):
    steps = []
    max_num = max(arr)
    digit_count = len(str(max_num))

    for digit in range(digit_count):
        buckets = [[] for _ in range(10)]
        for num in arr:
            digit_value = get_digit(num, digit)
            buckets[digit_value].append(num)

        arr = []
        for bucket in buckets:
            for num in bucket:
                arr.append(num)
                steps.append(arr.copy())

    return steps

# Route for the main page
@app.route('/')
def index():
    return render_template('index.html')

# Route for sorting algorithms
@app.route('/<algorithm>', methods=['POST'])
def visualize_sort(algorithm):
    arr = request.json['array']
    if algorithm == 'bubble_sort':
        steps = bubble_sort(arr)
    elif algorithm == 'selection_sort':
        steps = selection_sort(arr)
    elif algorithm == 'insertion_sort':
        steps = insertion_sort(arr)
    elif algorithm == 'merge_sort':
        steps = merge_sort(arr)
    elif algorithm == 'heap_sort':
        steps = heap_sort(arr)
    elif algorithm == 'quick_sort':
        steps = quick_sort(arr)
    elif algorithm == 'counting_sort':
        steps = counting_sort(arr)
    elif algorithm == 'bucket_sort':
        steps = bucket_sort(arr)
    elif algorithm == 'radix_sort':
        steps = radix_sort(arr)
    return jsonify(steps)

if __name__ == '__main__':
    app.run(debug=True)
