#!/usr/bin/env python
 
import wx

from MainWindow.MainWindow import MainWindow

def main():
    app = wx.App()  
    mainWindow = MainWindow(None)
    mainWindow.Show()
    app.MainLoop()

if __name__ == '__main__':
    main()
