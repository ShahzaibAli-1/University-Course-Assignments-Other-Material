import tkinter as tk
from tkinter import messagebox
import time

# Brute Force algorithm for searching
def brute_force_search(pattern, text):
    m = len(pattern)
    n = len(text)
    results = []


    for i in range(n - m + 1):
        match = True

        for j in range(m):
            if text[i + j] != pattern[j]:
                match = False
                break
        if match:
            results.append(i)  

    return results

def perform_search():
    search_string = entry_string.get().strip()
    match_word = check_match_word.get()
    match_case = check_match_string.get()

    if not search_string:
        messagebox.showwarning("Input Error", "Please enter a search string.")
        return

    start = time.time()

    # Load files
    files = [f'Research#{i}.txt' for i in range(1, 11)]
    file_contents = {}

    for file in files:
        try:
            with open(file, 'r', encoding='utf-8') as f:
                file_contents[file] = f.readlines()
        except Exception as e:
            messagebox.showerror("File Error", f"Error reading file {file}: {e}")
            return

    # Prepare result string
    result = f"Search Word: '{entry_string.get().strip()}'\n\n"

    for file, rows in file_contents.items():
        for row_num, row in enumerate(rows):
            words = row.split()
            word_count = len(words)

            if not match_case:
                row = row.lower()
                search_string = search_string.lower()

            if match_word:
                if search_string in words:
                    col = words.index(search_string)
                    result += f"Match found in file: {file}, row: {row_num + 1}, column: {col + 1}\n"

            else:
                match_positions = brute_force_search(search_string, row)
                if match_positions:
                    for col in match_positions:
                        col_word_index = len(row[:col].split())
                        result += f"Match found in file: {file}, row: {row_num + 1}, column: {col_word_index + 1}\n"

    if result:
        text_output.delete("1.0", tk.END)
        text_output.insert(tk.END, result)
    else:
        messagebox.showinfo("Search Results", "No matches found.")

    end = time.time()
    time_taken = f"\nTime taken: {end - start} seconds"
    text_output.insert(tk.END, time_taken)

# GUI Setup
root = tk.Tk()
root.title("Text Search Application")

tk.Label(root, text="Enter search string:").grid(row=0, column=0, padx=10, pady=10)
entry_string = tk.Entry(root, width=40)
entry_string.grid(row=0, column=1, padx=10, pady=10)

check_match_word = tk.BooleanVar()
check_match_string = tk.BooleanVar()

tk.Checkbutton(root, text="Match Word", variable=check_match_word).grid(row=1, column=0, padx=10, pady=5, sticky="w")
tk.Checkbutton(root, text="Match Case", variable=check_match_string).grid(row=1, column=1, padx=10, pady=5, sticky="w")

btn_search = tk.Button(root, text="Search", command=perform_search)
btn_search.grid(row=2, column=0, columnspan=2, pady=10)

text_output = tk.Text(root, height=15, width=80)
text_output.grid(row=3, column=0, columnspan=2, padx=10, pady=10)

root.mainloop()