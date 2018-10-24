from tkinter import *
from tkinter.filedialog import askopenfilename
import os
import xml.dom.minidom
import threading

node_num = 0
node_dealed = 0
dealed_temp = 0
one_percent = 1
in_change_num = 0
start_change_num = 0
collection = None
DOMTree = None
first = True
index = 0

def getFirst(nodes):
    global first
    if not first:
        return
    for i in range(len(nodes)):
        child_nodes = nodes[i].childNodes
        getFirst(child_nodes)
    start = None
    end = None
    for i in range(len(nodes)):
        if nodes[i].nodeName == "start":
            start = nodes[i].childNodes[0].data
        if nodes[i].nodeName == "end":
            end = nodes[i].childNodes[0].data
        if nodes[i].nodeName == "in" and start is not None:
            firstStart.set('first start:[{}]'.format(start))
            firstIn.set('first in:[{}]'.format(nodes[i].childNodes[0].data))
        if nodes[i].nodeName == "out" and end is not None:
            firstEnd.set('first end:[{}]'.format(end))
            firstOut.set('first out:[{}]'.format(nodes[i].childNodes[0].data))
            first = False

def sum_node(nodes):
    global node_num
    node_num = node_num + len(nodes)
    for i in range(len(nodes)):
        if nodes[i].nodeName == "clipindex":
            linked.set('yes')
        child_nodes = nodes[i].childNodes
        sum_node(child_nodes)

def get_result_name(file_name):
    str_list = file_name.split('/')
    name_list = str_list[len(str_list)-1].split('.')
    name_list[0] = name_list[0] + "-result"
    str_list[len(str_list)-1] = ".".join(name_list)
    result_file = '/'.join(str_list)
    return result_file

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

def deal_file(file_name):
    global node_dealed
    global first
    node_dealed = 0

    result_file = get_result_name(file_name)
    file = open(result_file, "wb")
    nodes = collection.childNodes

    solve.set("processing")
    solve_button.config(state="disabled")
    root.update()
    print(node_num)
    
    collection.childNodes = deal_with_node(nodes)
    dom_bytes = DOMTree.toxml(encoding="utf-8")
    file.write(dom_bytes)
    file.close()
    solve.set("start")
    solve_button.config(state="normal")

    first = True
    getFirst(nodes)
    root.update()

def change_node(nodes):
    global node_dealed
    global dealed_temp
    for i in range(len(nodes)):
        child_nodes = nodes[i].childNodes
        if len(child_nodes) > 0:
            nodes[i].childNodes = change_node(child_nodes)
    start = None
    end = None
    for i in range(len(nodes)):
        if nodes[i].nodeName == "start":
            start = nodes[i]
        if nodes[i].nodeName == "end":
            end = nodes[i]
        if nodes[i].nodeName == "in" and start is not None:
            num = int(nodes[i].childNodes[0].data) + in_change_num
            nodes[i].childNodes[0].data = str(num)
            num = int(start.childNodes[0].data) + start_change_num
            start.childNodes[0].data = str(num)
        if nodes[i].nodeName == "out" and end is not None:
            num = int(nodes[i].childNodes[0].data) + in_change_num
            nodes[i].childNodes[0].data = str(num)
            num = int(end.childNodes[0].data) + start_change_num
            end.childNodes[0].data = str(num)
    dealed_temp = dealed_temp + len(nodes)
    node_dealed = node_dealed + len(nodes)
    if dealed_temp >= one_percent or node_dealed >= node_num:
        add_coords()
        dealed_temp = 0
    return nodes

def change_num(file_name):
    global start_change_num
    global in_change_num
    global first
    global node_dealed

    first = True
    node_dealed = 0
    start_change_num = int(startChange.get())
    in_change_num = int(inChange.get())
    change_button.config(state="disabled")
    root.update()

    result_file = get_result_name(file_name)
    file = open(result_file, "wb")
    nodes = collection.childNodes
    
    collection.childNodes = change_node(nodes)
    dom_bytes = DOMTree.toxml(encoding="utf-8")
    file.write(dom_bytes)
    file.close()
    change_button.config(state="normal")

    getFirst(nodes)
    root.update()

def link_node(nodes):
    global node_dealed
    global dealed_temp
    global index

    for i in range(len(nodes)):
        if nodes[i].nodeName == "video" or nodes[i].nodeName == "audio":
            index = 0
        child_nodes = nodes[i].childNodes
        if len(child_nodes) > 0:
            nodes[i].childNodes = link_node(child_nodes)
    for i in range(len(nodes)):
        if nodes[i].nodeName == "link":
            index = index + 1
            text = 'audio'
            indexStr = ''
            if index % 2 == 1:
                text = 'video'
                indexStr = str(int((index+1)/2))
            else:
                indexStr = str(int(index / 2))
            mediatype=DOMTree.createElement('mediatype')
            mediatype.appendChild(DOMTree.createTextNode(text))
            nodes[i].appendChild(mediatype)
            trackindex=DOMTree.createElement('trackindex')
            trackindex.appendChild(DOMTree.createTextNode('1'))
            nodes[i].appendChild(trackindex)
            clipindex=DOMTree.createElement('clipindex')
            clipindex.appendChild(DOMTree.createTextNode(indexStr))
            nodes[i].appendChild(clipindex)
    dealed_temp = dealed_temp + len(nodes)
    node_dealed = node_dealed + len(nodes)
    if dealed_temp >= one_percent or node_dealed >= node_num:
        add_coords()
        dealed_temp = 0
    return nodes

def link_num(file_name):
    global node_dealed
    global index
    global node_num

    node_dealed = 0
    index = 0
    link_button.config(state="disabled")
    root.update()

    result_file = get_result_name(file_name)
    file = open(result_file, "wb")
    nodes = collection.childNodes
    
    collection.childNodes = link_node(nodes)
    dom_bytes = DOMTree.toxml(encoding="utf-8")
    file.write(dom_bytes)
    file.close()

    node_num = 0
    sum_node(nodes)
    linked.set('yes')

    root.update()

def select_file():
    global collection
    global DOMTree
    global one_percent
    global node_num

    path_ = askopenfilename(initialdir=os.getcwd())
    path.set(path_)
    solve_button.config(state="normal")
    change_button.config(state="normal")
    DOMTree = xml.dom.minidom.parse(path.get())
    collection = DOMTree.documentElement
    nodes = collection.childNodes

    node_num = 0
    sum_node(nodes)
    getFirst(nodes)
    one_percent = int(node_num / 100)

    if linked.get() == 'no':
        link_button.config(state="normal")

root = Tk()
root.geometry('550x200')
path = StringVar()
percentage = StringVar()
percentage.set("0%")
solve = StringVar()
solve.set("start")

startChange = StringVar()
startChange.set('0')
inChange = StringVar()
inChange.set('0')

firstStart = StringVar()
firstStart.set('first start:[0]')
firstEnd = StringVar()
firstEnd.set('first end:[0]')
firstIn = StringVar()
firstIn.set('first in:[0]')
firstOut = StringVar()
firstOut.set('first out:[0]')

linked = StringVar()
linked.set('no')

Label(root, text = "xml to be modified：").grid(row = 0, column = 0)
Entry(root, textvariable = path, width = 30).grid(row = 0, column = 1)
Button(root, text="select", width = 10, height = 1, command=select_file).grid(row = 0, column = 2)
canvas = Canvas(root,width = 200, height = 26,bg = "white")
out_line = canvas.create_rectangle(2,2,210,27,width = 1, outline = "black")
canvas.grid(row = 1, column = 0, ipadx = 5)
fill_line = canvas.create_rectangle(2,2,0,27,width = 0, fill = "blue") 
Label(root, textvariable = firstStart).grid(row = 2, column = 0)
Label(root, textvariable = firstEnd).grid(row = 2, column = 1)
Label(root, textvariable = firstIn).grid(row = 3, column = 0)
Label(root, textvariable = firstOut).grid(row = 3, column = 1)
Label(root, text = "start/end:").grid(row = 4, column = 0)
Entry(root, textvariable = startChange, width = 20).grid(row = 4, column = 1)
Label(root, text = "in/out:").grid(row = 5, column = 0)
Entry(root, textvariable = inChange, width = 20).grid(row = 5, column = 1)

Label(root, textvariable = percentage).grid(row = 1, column = 1)
solve_button = Button(root, textvariable=solve, width = 10, height = 1, command=lambda : deal_file(file_name = path.get()))
solve_button.grid(row = 1, column = 2)
solve_button.config(state="disabled")

change_button = Button(root, text='change', width = 10, height = 1, command=lambda : change_num(file_name = path.get()))
change_button.grid(row = 5, column = 2)
change_button.config(state="disabled")


Label(root, text = "linked:").grid(row = 6, column = 0)
Label(root, textvariable = linked).grid(row = 6, column = 1)
link_button = Button(root, text='link', width = 10, height = 1, command=lambda : link_num(file_name = path.get()))
link_button.grid(row = 6, column = 2)
link_button.config(state="disabled")

root.mainloop()