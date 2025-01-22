import wx

from MainWindow.MainMenu import MainMenu
from DataModel.DataModel import DataModel
from ProjectWindow.ProjectWindow import ProjectWindow
from Util.Object import Object
from Util.SignalModel import SignalModel
from Util.ConfigXml import ConfigXml

#
# Main window of the application
#
class MainWindow(wx.Frame):
    
    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        
        # Create window model
        self.windowModel = {}
        
        # Create instances
        self.createInstances()
          
        # Init ui
        self.initUI()
        
    
    def createInstances(self):
        
        # Create signal model
        self.signalModel = SignalModel()
        self.signalModel.addSignals([
            "DataModel.TitleChangedSignal",         # Data from title changed
            "DataModel.StatusBarChangedSignal",     # Data from status bar changed
            "DataModel.DataChangedSignal",          # Data from data model changed
            "ProjectTree.ItemSignal"                # Project tree item signal
        ])
        
        # Create data model
        self.configXml = ConfigXml() 
        configModel = Object({
            "read": self.configXml.read,
            "write": self.configXml.write  
        })
        self.dataModel = DataModel(
            self.signalModel,
            configModel
        )
        
        # Create main menu instance
        self.windowModel["MainMenu"] = MainMenu(
            self, 
            self.dataModel, 
            self.windowModel,
            self.signalModel
        )
        
        # Create project window instance
        self.windowModel["ProjectWindow"] = ProjectWindow(
            self, 
            self.dataModel, 
            self.windowModel,
            self.signalModel
        )
        
        
    def initUI(self):
       
        # Init main menu
        self.windowModel["MainMenu"].initUI()
        
        # Init project window
        self.windowModel["ProjectWindow"].initUI()
        
        # Set main window attributes
        self.titleChangedEvent(0, None)
        self.SetSize(1000, 600)
        self.Centre()
        
        # Init event handler
        self.signalModel.addSlot(
            "DataModel.TitleChangedSignal", 
            self.titleChangedEvent, 
            "MainWindow.TitleChangedSlot"
        )
        
    def titleChangedEvent(self, event, data):
        self.SetTitle(self.dataModel.title)
        