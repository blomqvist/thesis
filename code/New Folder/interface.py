from Tkinter import *
from ttk import Frame, Button, Style



class Example(Frame):  
    def __init__(self, parent):
        Frame.__init__(self, parent)   
         
        self.parent = parent
        
        self.initUI()


    def initUI(self):
      
        self.parent.title("Truck")
        
        self.style = Style()
        self.style.theme_use("default")

        self.pack(fill=BOTH, expand=1)

        slider = Scale(self, from_=-100, to=100, orient=HORIZONTAL, length=700)
        slider.place(x=50, y=350)

        slider2 = Scale(self, from_=100, to=0, length=250)
        slider2.place(x=25, y=50)

        slowdown = StringVar()
        message = Label(self, textvariable=slowdown)
        message.place(x=100, y=300)

        def update():
            print slider.get()
            print slider2.get()
            if slider2.get() > 80:
                slowdown.set("Slow Down!")
            else:
                slowdown.set("          ")    
            
            self.after(20, update)

        self.after(20, update)


    
        

def main():

    root = Tk()
    
    root.geometry("800x400+300+300")

    app = Example(root)

    root.mainloop()  

if __name__ == '__main__':
    main()