from tkinter import *
from tkinter.filedialog import askopenfilename
import os
import xml.dom.minidom
import threading

node_num = 0
node_dealed = 0
dealed_temp = 0
one_percent = 1
finished = False

def sum_node(nodes):
    global node_num
    node_num = node_num + len(nodes)
    for i in range(len(nodes)):
        child_nodes = nodes[i].childNodes
        sum_node(child_nodes)

def add_coords():
    canvas.coords(fill_line, (0, 0, 210*node_dealed/node_num, 30))
    percentage.set(str(int(node_dealed/node_num * 100))+"%")
    root.update()

def deal_with_node(nodes):
    global node_dealed
    global dealed_temp
    for i in range(len(nodes)):
        child_nodes = nodes[i].childNodes
        if len(child_nodes) > 0:
            nodes[i].childNodes = deal_with_node(child_nodes)
    start = None
    end = None
    for i in range(len(nodes)):
        if nodes[i].nodeName == "start":
            start = nodes[i].childNodes[0].data
        if nodes[i].nodeName == "end":
            end = nodes[i].childNodes[0].data
        if nodes[i].nodeName == "in" and start is not None:
            nodes[i].childNodes[0].data = start
        if nodes[i].nodeName == "out" and end is not None:
            nodes[i].childNodes[0].data = end
    dealed_temp = dealed_temp + len(nodes)
    node_dealed = node_dealed + len(nodes)
    if dealed_temp >= one_percent or node_dealed >= node_num:
        add_coords()
        dealed_temp = 0
    return nodes

def get_result_name(file_name):
    str_list = file_name.split('/')
    name_list = str_list[len(str_list)-1].split('.')
    name_list[0] = name_list[0] + "-result"
    str_list[len(str_list)-1] = ".".join(name_list)
    result_file = '/'.join(str_list)
    return result_file

def deal_file(file_name):
    global one_percent
    global finished
    if finished:
        root.destroy()
        return
    solve.set("pending...")
    solve_button.config(state="disabled")
    root.update()

    DOMTree = xml.dom.minidom.parse(file_name)
    result_file = get_result_name(file_name)
    file = open(result_file, "wb")
    collection = DOMTree.documentElement
    nodes = collection.childNodes

    sum_node(nodes)
    one_percent = int(node_num / 100)
    solve.set("processing")
    root.update()
    print(node_num)
    
    collection.childNodes = deal_with_node(nodes)
    dom_bytes = DOMTree.toxml(encoding="utf-8")
    file.write(dom_bytes)
    file.close()
    solve.set("finish")
    root.update()
    finished = True
    solve_button.config(state="normal")
    print("finished")

def select_file():
    global finished
    finished = False
    path_ = askopenfilename(initialdir=os.getcwd())
    path.set(path_)
    solve_button.config(state="normal")

root = Tk()
root.geometry('550x100')
path = StringVar()
percentage = StringVar()
percentage.set("0%")
solve = StringVar()
solve.set("start")

Label(root, text = "xml to be modified：").grid(row = 0, column = 0)
Entry(root, textvariable = path, width = 30).grid(row = 0, column = 1)
Button(root, text="select", width = 10, height = 1, command=select_file).grid(row = 0, column = 2)
canvas = Canvas(root,width = 200, height = 26,bg = "white")
out_line = canvas.create_rectangle(2,2,210,27,width = 1, outline = "black")
canvas.grid(row = 1, column = 0, ipadx = 5)
fill_line = canvas.create_rectangle(2,2,0,27,width = 0, fill = "blue") 

Label(root, textvariable = percentage).grid(row = 1, column = 1)
solve_button = Button(root, textvariable=solve, width = 10, height = 1, command=lambda : deal_file(file_name = path.get()))
solve_button.grid(row = 1, column = 2)
solve_button.config(state="disabled")

root.mainloop()