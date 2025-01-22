import wx
import os.path

from DataModel.DataModel import DataModelState
from Util.Base import resource_path

MENU_FILE_NEW_ITEM = 1
MENU_FILE_OPEN_ITEM = 2
MENU_FILE_SAVE_ITEM = 3
MENU_FILE_SAVE_AS_ITEM = 4
MENU_FILE_CLOSE_ITEM = 5
MENU_FILE_QUIT_ITEM = 6

class MainMenu():
    
    def __init__(self, parent, dataModel, windowModel, signalModel):
        self.parent = parent
        self.dataModel = dataModel
        self.windowModel = windowModel
        self.signalModel = signalModel
        self.image_path = resource_path("./Icons")
        
    def initUI(self):     
        self.initMenuUI()
        self.initToolbarUI()
        self.initStatusBarUI()
        self.initMenuAction()
        
        self.statusBarChangedEvent(0, None)
        self.dataChangedEvent(0, None)
        
        # Init event handler
        self.signalModel.addSlot(
            "DataModel.StatusBarChangedSignal", 
            self.statusBarChangedEvent, 
            "MainMenu.StatusBarChangedSlot"
        )
        self.signalModel.addSlot(
            "DataModel.DataChangedSignal", 
            self.dataChangedEvent, 
            "MainMenu.DataChangedSlot"
        )
        
        
    def initFileMenuUI(self):
        
        #
        # Create file menu
        #
        self.menuFile = wx.Menu()
        
        # New menu item
        self.menuFileNewItem = wx.MenuItem(self.menuFile, MENU_FILE_NEW_ITEM, '&New')
        self.menuFile.Append(self.menuFileNewItem)
        
        # Open menu item
        self.menuFileOpenItem = wx.MenuItem(self.menuFile, MENU_FILE_OPEN_ITEM, '&Open')
        self.menuFile.Append(self.menuFileOpenItem)
        
        # Save menu item
        self.menuFileSaveItem = wx.MenuItem(self.menuFile, MENU_FILE_SAVE_ITEM, '&Save')
        self.menuFile.Append(self.menuFileSaveItem)
        
        # Save as menu item
        self.menuFileSaveAsItem = wx.MenuItem(self.menuFile, MENU_FILE_SAVE_AS_ITEM, 'Save&As')
        self.menuFile.Append(self.menuFileSaveAsItem)
        
        # Close menu item
        self.menuFileCloseItem = wx.MenuItem(self.menuFile, MENU_FILE_CLOSE_ITEM, '&Close')
        self.menuFile.Append(self.menuFileCloseItem)
        
        # Add seperator
        self.menuFile.AppendSeparator()
        
        # Quit menu item
        self.menuFilQuitItem = wx.MenuItem(self.menuFile, MENU_FILE_QUIT_ITEM, '&Quit')
        self.menuFile.Append(self.menuFilQuitItem)
   
   
    def initMenuUI(self):
        # Create new menu bar
        self.menuBar = wx.MenuBar()
        
        self.initFileMenuUI()
        self.menuBar.Append(self.menuFile, '&File')
        
        
        # Add menu bar to parent
        self.parent.SetMenuBar(self.menuBar)
        
        
    def initToolbarUI(self):
        
        self.toolbar = self.parent.CreateToolBar()
        
        # Create file items
        self.toolbarFileNewItem = self.toolbar.AddTool(MENU_FILE_NEW_ITEM, "New", wx.Bitmap(self.image_path + "/file_32.png"))
        self.toolbarFileOpenItem = self.toolbar.AddTool(MENU_FILE_OPEN_ITEM, "Open", wx.Bitmap(self.image_path + "/folder_opened_32.png"))
        self.toolbarFileSaveItem = self.toolbar.AddTool(MENU_FILE_SAVE_ITEM, "Save", wx.Bitmap(self.image_path + "/save_32.png"))
        self.toolbarFileSaveAsItem = self.toolbar.AddTool(MENU_FILE_SAVE_AS_ITEM, "SaveAs", wx.Bitmap(self.image_path + "/save_as_32.png"))
        self.toolbarFileCloseItem = self.toolbar.AddTool(MENU_FILE_CLOSE_ITEM, "Close", wx.Bitmap(self.image_path + "/folder_closed_32.png"))
        
        self.toolbar.Realize()
        
        
    def initStatusBarUI(self):
        # Create status bar
        self.statusBar = self.parent.CreateStatusBar()
        
        
    def statusBarChangedEvent(self, event, data):
        self.statusBar.SetStatusText(self.dataModel.statusBarText)
        if self.dataModel.statusBarError:
            self.statusBar.SetBackgroundColour(wx.RED) 
        else:
            self.statusBar.SetBackgroundColour(wx.NullColour) 
        
        
    def initMenuAction(self):
    
        #
        # Add file menu actions
        #
        self.parent.Bind(wx.EVT_MENU, self.OnFileNew, id=MENU_FILE_NEW_ITEM)
        self.parent.Bind(wx.EVT_MENU, self.OnFileNew, self.toolbarFileNewItem)
        
        self.parent.Bind(wx.EVT_MENU, self.OnFileOpen, id=MENU_FILE_OPEN_ITEM)
        self.parent.Bind(wx.EVT_MENU, self.OnFileOpen, self.toolbarFileOpenItem)
        
        self.parent.Bind(wx.EVT_MENU, self.OnFileSave, id=MENU_FILE_SAVE_ITEM)
        self.parent.Bind(wx.EVT_MENU, self.OnFileSave, self.toolbarFileSaveItem)
        
        self.parent.Bind(wx.EVT_MENU, self.OnFileSaveAs, id=MENU_FILE_SAVE_AS_ITEM)
        self.parent.Bind(wx.EVT_MENU, self.OnFileSaveAs, self.toolbarFileSaveAsItem)
        
        self.parent.Bind(wx.EVT_MENU, self.OnFileClose, id=MENU_FILE_CLOSE_ITEM)
        self.parent.Bind(wx.EVT_MENU, self.OnFileClose, self.toolbarFileCloseItem)
        
        self.parent.Bind(wx.EVT_MENU, self.OnQuit, id=MENU_FILE_QUIT_ITEM)
        
        
    def dataChangedEvent(self, event, data):
        # Check data model state
        if self.dataModel.state == DataModelState.Close: # Project is not open
            self.menuFileNewItem.Enable(True)
            self.menuFileOpenItem.Enable(True)
            self.menuFileSaveItem.Enable(False)
            self.menuFileSaveAsItem.Enable(False)
            self.menuFileCloseItem.Enable(False)
            self.toolbar.EnableTool(MENU_FILE_NEW_ITEM, True)
            self.toolbar.EnableTool(MENU_FILE_OPEN_ITEM, True)
            self.toolbar.EnableTool(MENU_FILE_SAVE_ITEM, False)
            self.toolbar.EnableTool(MENU_FILE_SAVE_AS_ITEM, False)
            self.toolbar.EnableTool(MENU_FILE_CLOSE_ITEM, False)
        elif self.dataModel.state == DataModelState.Open: # Project is open and not changed
            self.menuFileNewItem.Enable(True)
            self.menuFileOpenItem.Enable(True)
            self.menuFileSaveItem.Enable(False)
            self.menuFileSaveAsItem.Enable(False)
            self.menuFileCloseItem.Enable(True)
            self.toolbar.EnableTool(MENU_FILE_NEW_ITEM, True)
            self.toolbar.EnableTool(MENU_FILE_OPEN_ITEM, True)
            self.toolbar.EnableTool(MENU_FILE_SAVE_ITEM, False)
            self.toolbar.EnableTool(MENU_FILE_SAVE_AS_ITEM, False)
            self.toolbar.EnableTool(MENU_FILE_CLOSE_ITEM, True)
        else: # Project is open and changed
            self.menuFileNewItem.Enable(True)
            self.menuFileOpenItem.Enable(True)
            self.menuFileSaveItem.Enable(True)
            self.menuFileSaveAsItem.Enable(True)
            self.menuFileCloseItem.Enable(True)
            self.toolbar.EnableTool(MENU_FILE_NEW_ITEM, True)
            self.toolbar.EnableTool(MENU_FILE_OPEN_ITEM, True)
            self.toolbar.EnableTool(MENU_FILE_SAVE_ITEM, True)
            self.toolbar.EnableTool(MENU_FILE_SAVE_AS_ITEM, True)
            self.toolbar.EnableTool(MENU_FILE_CLOSE_ITEM, True)
            
        self.parent.Update()
        
        
    def OnQuit(self, e):
        self.parent.Close()
        
        
    def OnFileNew(self, e):
        
        # Save actual project
        if self.dataModel.state == DataModelState.Changed:
            
            # Ask user if the actual project should be saved
            dial = wx.MessageDialog(None, 'Save current project?', 'Question',
                wx.YES_NO | wx.NO_DEFAULT | wx.ICON_QUESTION)
            ret = dial.ShowModal()
            if ret == wx.ID_NO: return False

            # We must save an close the actual project
            if self.dataModel.projectPath == "Unnamed.xml":
                if self.OnFileSaveAs(None) == False: return False
            else:
                if self.OnFileSave(None) == False: return False
           
        # Close the actual project
        if self.dataModel.state != DataModelState.Close:
            self.dataModel.closeProject()
        
        # Create new project
        idx = 1
        path = os.getcwd() + "/" + "Unnamed.xml"
        while os.path.exists(path):
            path = os.getcwd() + "/" + "Unnamed" + str(idx) + ".xml"
            idx = idx + 1
        self.dataModel.newProject(path);
        
        return True
        
    
    # FIXME: Rework    
    def OnFileOpen(self, e):
        # Select project path
        if self.dataModel.state == DataModelState.Changed:
            # Ask user if the project should be saved
            dial = wx.MessageDialog(None, 'Save current project?', 'Question',
                wx.YES_NO | wx.NO_DEFAULT | wx.ICON_QUESTION)
            ret = dial.ShowModal()
            if ret == wx.ID_NO: return False
            
            # We must save an close the actual project
            if self.dataModel.projectPath == "Unnamed.xml":
                if self.OnFileSaveAs(None) == False: return False
            else:
                if self.OnFileSave(None) == False: return False
           
            # Close the project
            self.dataModel.closeProject()
            self.windowModel["ProjectWindow"].closeProject()   
         
        # Select project file
        fileDialog = wx.FileDialog(
            self.parent, "Open project file", wildcard="*.xml",
            style=wx.FD_OPEN | wx.FD_FILE_MUST_EXIST
        )
        if fileDialog.ShowModal() == wx.ID_CANCEL:
            return False
        
        # Open project
        path = fileDialog.GetPath()
        if self.dataModel.openProject(path) == False:
            msg = "Open project file " + path + " error" 
            wx.MessageBox(msg, 'Error', wx.OK | wx.ICON_ERROR)
            return False
        
        return True
    
    
    def OnFileSave(self, e):
        # Save project
        path = self.dataModel.projectPath
        if self.dataModel.saveProject(path) == False:
            msg = "Save project file " + path + " error"
            wx.MessageBox(msg, 'Error', wx.OK | wx.ICON_ERROR)
            return False
  
        return True
    
    
    def OnFileSaveAs(self, e):
        # Select project path
        fileDialog = wx.FileDialog(
            self.parent, "Save project file", wildcard="*.xml",
            style=wx.FD_SAVE | wx.FD_OVERWRITE_PROMPT
        )
        fileDialog.SetPath(self.dataModel.projectPath)
        if fileDialog.ShowModal() == wx.ID_CANCEL:
            return False
        
        # Save project
        self.dataModel.projectPath = fileDialog.GetPath()
        rc = self.OnFileSave(None)
        
        return rc
    
    
    def OnFileClose(self, e):
        # Save actual project
        if self.dataModel.state == DataModelState.Changed:
            # Ask user if the project should be saved
            dial = wx.MessageDialog(None, 'Save current project?', 'Question',
                wx.YES_NO | wx.NO_DEFAULT | wx.ICON_QUESTION)
            ret = dial.ShowModal()
            if ret == wx.ID_YES: 
                fileDialog = wx.FileDialog(
                    self.parent, "Save project file", wildcard="*.xml",
                    style=wx.FD_SAVE | wx.FD_OVERWRITE_PROMPT
                )
                fileDialog.SetPath(self.dataModel.projectPath)
                if fileDialog.ShowModal() == wx.ID_CANCEL:
                    return False
        
                # Save project
                self.dataModel.projectPath = fileDialog.GetPath()
                self.OnFileSave(None)
            
        # Close project
        self.dataModel.closeProject()
        
        