from __future__ import print_function
from Tkinter import *
from ttk import Frame, Button, Style
from PIL import Image, ImageTk
from threading import Thread

class Truck(Frame):
    rpm_slider = None
    bfly_slider = None
    steer_slider = None
    height_slider = None
    weight_slider = None
    adlift_slider = None

    height_label = None
    weight_label = None

    height_variable = 0

    height_indicator1_label = None
    height_indicator2_label = None

    override_label = None

    restrict_hydr_label  = None
    restrict_steer_label = None
    restrict_drive_label = None

    flash_left_img = None
    flash_right_img = None

    indicator_left_on = None
    indicator_left_off = None

    indicator_right_on = None
    indicator_right_off = None

    indicator_left = None
    indicator_right = None

    defaultbg = None

    slower_change = None
    restricted = False
    restricted_drive = False
    override = False

    queue = None
    can_queue = None # Data sent from server

    def __init__(self, parent, queue, can_queue):
        Frame.__init__(self, parent)
        self.can_queue = can_queue
        self.queue = queue
        self.parent = parent
        self.initUI()
        self.slower_change = 0

        # Create a thread and monitor can_queue
        can_w = Thread(target = self.handle_can_queue)
        can_w.daemon = True
        can_w.start()

    def handle_can_queue(self):
        while True:
            item = self.can_queue.get()
            if item and "=" in item:
                item = item.split("=")
                try:
                    item[1] = int(item[1])
                except:
                    pass

                if item[0] == "INDICATOR_LEFT":
                    if item[1] == 1:
                        self.set_flash_left()
                        self.clear_flash_right()
                    else:
                        self.clear_flash_left()
                elif item[0] == "INDICATOR_RIGHT":
                    if item[1] == 1:
                        self.set_flash_right()
                        self.clear_flash_left()
                    else:
                        self.clear_flash_right()
                elif item[0] == "OVERRIDE":
                    self.override = True if item[1] == 1 else False
                    if item[1] == 1:
                        self.set_override_label()
                    else:
                        self.clear_override_label()

                elif item[0] == "DILIFT1UP" and item[1] == 1:
                    self.slower_change += 1
                    if self.restricted == False and self.slower_change % 10 == 0:
                        self.height_slider.set(self.height_slider.get() + 10)

                elif item[0] == "DILIFT1DOWN" and item[1] == 1:
                    self.slower_change += 1
                    if self.slower_change % 10 == 0:
                        self.height_slider.set(self.height_slider.get() - 10)

                elif item[0] == "RESTRICT_HYDR":
                    self.restricted = True if item[1] == 1 else False
                    if self.restricted == True:
                        self.restrict_hydr_label.configure(bg = "red")
                    else:
                        self.restrict_hydr_label.configure(bg = self.defaultbg)

                elif item[0] == "RESTRICT_STEER":
                    if item[1] == 1:
                        self.restrict_steer_label.configure(bg = "red")
                    else:
                        self.restrict_steer_label.configure(bg = self.defaultbg)

                elif item[0] == "RESTRICT_DRIVE":
                    self.restricted_drive = True if item[1] == 1 else False
                    if item[1] == 1:
                        self.restrict_drive_label.configure(bg = "red")
                    else:
                        self.restrict_drive_label.configure(bg = self.defaultbg)

                elif item[0] == "RESTRICT_DRIVE_SPEED":
                    if self.restricted_drive == True:
                        self.rpm_slider.set(int(item[1]))
                        self.rpm_slider.configure(bg = "red")
                    else:
                        self.rpm_slider.set(0)
                        self.rpm_slider.configure(bg = self.defaultbg)     

                elif item[0] == "BFLY":
                    self.set_bfly_slider(item[1])


    def initUI(self):
        self.parent.title("Truck")
        self.style = Style()
        self.style.theme_use("default")

        self.pack(fill = BOTH, expand = 1)

        # SLIDERS
        self.steer_slider = Scale(self, to = 100, from_ = -100, orient = HORIZONTAL, length = 700, command=self.updateSteerSlider)
        self.steer_slider.place(x = 50, y = 350)

        self.rpm_slider = Scale(self, to = -32508, from_ = 32507, length = 250, command = self.updateRpmSlider)
        self.rpm_slider.place(x = 5, y = 50)

        self.bfly_slider = Scale(self, to = -32508, from_ = 32507, length = 250)
        self.bfly_slider.place(x = 120, y = 50)
        
        self.adlift_slider = Scale(self, to_= -128, from_ = 127, length = 250, command = self.updateAdLiftSlider)
        self.adlift_slider.place(x = 710, y = 50)

        self.height_slider = Scale(self, to = 0, from_ = 250, length = 200, resolution = 10, command = self.set_height_slider)
        self.height_slider.place(x = 400, y = 50)

        self.weight_slider = Scale(self, to = 0, from_ = 3000, length = 200, resolution = 100, command = self.set_weight_slider)
        self.weight_slider.place(x = 300, y = 50)

        # LABELS
        self.height_label = Label(self, text = "cm")
        self.height_label.place(x = 405, y = 30)

        self.weight_label = Label(self, text = "kg")
        self.weight_label.place(x = 310, y = 30)

        Label(self, text = "Fork properties").place(x = 340, y = 10)

        self.height_indicator1_label = Label(self, text = "    ", bg = "green")
        self.height_indicator1_label.place(x = 455, y = 150)

        self.height_indicator2_label = Label(self, text = "    ", bg = "green")
        self.height_indicator2_label.place(x = 455, y = 80)

        self.override_label = Label(self, text = "Override", bg = None)
        self.override_label.place(x = 500, y = 150)

        self.restrict_hydr_label = Label(self, text = "Restrict HYDR", bg = None)
        self.restrict_hydr_label.place(x = 500, y = 120)

        self.restrict_steer_label = Label(self, text = "Restrict STEER", bg = None)
        self.restrict_steer_label.place(x = 500, y = 100)
        
        self.restrict_drive_label = Label(self, text = "Restrict DRIVE", bg = None)
        self.restrict_drive_label.place(x = 500, y = 80)

        # OUTPUT
        self.indicator_left_off = ImageTk.PhotoImage(Image.open("LeftOff.png"))
        self.indicator_left_on = ImageTk.PhotoImage(Image.open("LeftOn.png"))

        self.indicator_right_off = ImageTk.PhotoImage(Image.open("RightOff.png"))
        self.indicator_right_on = ImageTk.PhotoImage(Image.open("RightOn.png"))

        self.flash_left_img = Label(self, image = self.indicator_left_off)
        self.flash_left_img.image = self.indicator_left_off
        self.flash_left_img.place(x = 90, y = 50)

        self.flash_right_img = Label(self, image = self.indicator_right_off)
        self.flash_right_img.image = self.indicator_right_off
        self.flash_right_img.place(x = 660, y = 50)

        chrUp = u'\u25B2'
        chrDown = u'\u25BC'

        # INPUT
        buttonRight = Button(self, text="Right", command = self.updateRightIndicator)
        buttonRight.place(x =685, y = 300, anchor = CENTER)

        buttonLeft = Button(self, text="Left", command = self.updateLeftIndicator)
        buttonLeft.place(x =120, y = 300, anchor = CENTER)

        buttonExtra1 = Button(self, text="Option Button 1", command = self.updateExtra1)
        buttonExtra1.place(x = 685, y = 340, anchor = CENTER)

        buttonExtra2 = Button(self, text="Option Button 2", command = self.updateExtra2)
        buttonExtra2.place(x =130, y = 340, anchor = CENTER)

        buttonDiLift2Up = Button(self, text=chrUp, command = self.updateDiLift2Up)
        buttonDiLift2Up.place(x = 300, y = 300, anchor = CENTER)

        buttonDiLift2Down = Button(self, text=chrDown, command = self.updateDiLift2Down)
        buttonDiLift2Down.place(x = 300, y = 340, anchor = CENTER)

        buttonDiLift1Up = Button(self, text=chrUp, command = self.updateDiLift1Up)
        buttonDiLift1Up.place(x = 400, y = 300, anchor = CENTER)

        buttonDiLift2Down = Button(self, text=chrDown, command = self.updateDiLift1down)
        buttonDiLift2Down.place(x = 400, y = 340, anchor = CENTER)

        buttonHorn = Button(self, text="Horn", command = self.updateHorn)
        buttonHorn.place(x = 500, y = 300, anchor = CENTER)

        buttonBelly = Button(self, text="Belly Button", command = self.updateBelly)
        buttonBelly.place(x = 500, y = 340, anchor = CENTER)

        self.defaultbg = self.parent["bg"]

    # PUBLIC FUNCTIONS   
    def set_flash_left(self):
        self.flash_left_img.configure(image = self.indicator_left_on)

    def clear_flash_left(self):
        self.flash_left_img.configure(image = self.indicator_left_off)

    def set_flash_right(self):
        self.flash_right_img.configure(image = self.indicator_right_on)

    def clear_flash_right(self):
        self.flash_right_img.configure(image = self.indicator_right_off)


    # PRIVATE FUNCTIONS
    def updateSteerSlider(self, value):
        self.queue.put("STEER_ANGLE=" + str(value))

    def updateRpmSlider(self, value):
        self.queue.put("SPEED=" + str(value))

    def updateAdLiftSlider(self, value):
        self.queue.put("ADLIFT1=" + str(value))

    def updateDiLift2Up(self):
        self.queue.put("DILIFT2=" + str(1))

    def updateDiLift2Down(self):
        self.queue.put("DILIFT2=" + str(0))

    def updateDiLift1Up(self):
        self.queue.put("DILIFT1=" + str(1))

    def updateDiLift1down(self):
        self.queue.put("DILIFT1=" + str(0))

    def updateHorn(self):
        self.queue.put("HORN=" + str(1))

    def updateBelly(self):
        self.queue.put("BELLY=" + str(1))

    def updateLeftIndicator(self):
        self.queue.put("LEFTINDICATOR=" + str(1))

    def updateRightIndicator(self):
        self.queue.put("RIGHTINDICATOR=" + str(1))

    def updateExtra1(self):
        self.queue.put("OPTIONBUTTON1=" + str(1))

    def updateExtra2(self):
        self.queue.put("OPTIONBUTTON2=" + str(1))

    def set_height_slider(self, value):
        self.queue.put("FORK_HEIGHT=" + value)
        
        value = int(value)
        if value > 100:
            self.height_indicator1_label.configure(bg = "red")
        else:
            self.height_indicator1_label.configure(bg = "green")

        if value > 200:
            self.height_indicator2_label.configure(bg = "red")
        else:
            self.height_indicator2_label.configure(bg = "green")

    def set_weight_slider(self, value):
        self.queue.put("FORK_WEIGHT=" + value)

    def set_override_label(self):
        self.override_label.configure(bg = "orange")

    def clear_override_label(self):
        self.override_label.configure(bg = self.defaultbg)

    def set_bfly_slider(self, value):
        self.bfly_slider.set(value)
        if abs(value) > 25000:
            self.bfly_slider.configure(bg = "red")
        elif abs(value) > 15000:
            self.bfly_slider.configure(bg = "orange")
        else:
            self.bfly_slider.configure(bg = self.defaultbg)