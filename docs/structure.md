## Program structure

**DISCLAIMER:** This document is a draft.   

### Observer (interface):   
Defines an entity as an observer of events.
#### methods:   
* update( event ) fires an update according to event that was received.


### Subject (inteface):   
Makes an entity observable.
#### methods:   
* registerObserver( Observer& ) add an observer object to 'to be notified' list.
* removeObserver( Observer& ) remove an observer object from the notification list.
* notify( event ) notify the observers of an event.


### DiffResult:
Container for the differences of an image.
#### variables:
* a vector which holds a tuple of x,y coordinates and the percentage of difference for 	the alpha channel.
*	//		//		//		//		//		the RGB  value.
*	//		//		//		//		//		the HSV  value.


### AbstractModel (interface):   
Provides facilities to access the images, the diff cache and defines comparison functionalities.
#### methods:   
* loadImage( path ) loads an image onto the storage.  
* loadImages( paths ) loads a list of images onto the storage. 
* removeImage( path ) unloads a specific image.   
* removeAllImages() unloads every image from the storage.   
* getImage( path ) returns the selected image.   
* getAllImages() returns all the images as path-image pairs. Useful for refreshing a list of images in the UI.   
* comparePixelRGB( rgb1&, rgb2& ) returns the difference between the two rgb colors in percentage.  
* comparePixelHSV( hsv1&, hsv2& ) returns the difference between the two hsv colors in percentage.  
* comparePixelAlpha( alpha1&, alpha2& ) returns the difference between the two alpha values in percentage.   
* compareRGB( path1, path2, color_tolerance ) compares the images indicated by their path, using the above comparePixelRgb() function, then saves those differences in the storage. The tolerance parameter excludes pixels in which the difference percentage is too low.
* compareHSV( path1, path2, color_tolerance ) does the same as compareRGB, but uses comparePixelHSV internally.
* compareAlpha( path1, path2, alpha_tolerance ) again the same as above, with comparePixelAlpha.
* getDifferences( path1, path2 ) returns a DiffResult structure which holds the differences betweeen those images. The order of the parameters does not count, as a comparison is the same in both directions.
* removeCachedDifferences( path1, path2 ) deletes the cached differences for the specified images, if any.
* removeAllCachedDifferences() deletes all the differences saved in the cache.


### Model:
Implements the interface of AbstractModel and defines the storage.
Implements the subject interface as well, thus becoming observable.
#### variables:   
* has a map storage that can hold multiple entries. Each entry is a pair key-element that holds an image and a string representing its path.   
* has a map storage that can hold multiple images comparisons. Each entry has a pair of the images compared as key and holds a DiffResult structure.
* a vector which takes note of the observers of the entity itself.


### AbstractView (interface):
#### methods:   
* removeImages(wxCommandEvent& event) asks the controller to remove the selected items from the image storage.
* loadImages(wxCommandEvent& event) gets an array of paths from the file chooser and asks the controller to load them.
* activateSelectedImages(wxCommandEvent& event) marks the first two selected images as active and shows them. This marks the previously activated images as inactive, and each tab is reset to its original state.
* compareImages(wxCommandEvent& event) asks the controller to compare the active images, by calling the appropriate function as selected in the modeSelector.
* resetTabs() resets all the tabs to their original state. It is called when other images are activated or when an active image is deleted from the storage.


### View:
Implements the interface of AbstractView.
#### variables:   
* the first active image.
* the other active image.
* a slider for the alpha tolerance, which holds the value internally.
* a slider for the color tolerance. //    //    //
* a list view which is used to show the stored images.
* a button which is used to add more images to the storage.
* a button which removes the images selected in the list, from the storage.
* a button which activates the first two selected images.
* a button which starts the image comparison.
* a combo box to select the comparison mode.
* an array of tabs that provide different ways of visualising the differences between those images.
* a messageBox for notification.
* the instance of AbstractModel responsible for accessing the storage.
* the instance of the AbstractController which handles the requests of the view.


### ViewTab (interface):
Defines a tab used to show the differences between images.
#### methods:
* reset() resets the tab to a clean slate.
* generateDiffView() processes the view's differences.


# WORK STOPPED HERE:
### Tabs:
The entities defined below are all realizations of ViewTab and all share an instance of the model passed to them by the view.

#### OriginalViewTab:
This tab shows the original images without any modification whatsoever. Gets the images from the model and converts them to static bitmaps for visualisation.
#### DiffListTab:
This tab has no images. It shows the list of differences with a table. No conversions are needed, it should be the fastest view.
##### NOTE: It may be possible to implement a save to file functionality for this view.
#### SideBySideTab:
Shows the two images side by side. Changes the pixels which are different (over the imposed tolerance) with a bright color to highlight them. The images are then converted to static bitmaps.
#### Image overlay (per type):
Should work in the same way as the sliding-view from Kaleidoscope. A slider changes how much of an image is shown, over another.
Different pixels are highlighted only in one image, thus sliding shows (or not) the differences.
#### Heatmap (per type):
TaKES THE Concept of a thermal camera and applies it to the differences. The original images are grayed out, then the result of the calculations are mapped to a range of color, from a darker (small difference) to a brighter (big difference) color per pixel.


### NOTES:
1. We might use two sliders to compare colors and alpha differences separately.   
2. The slider for color differences just passes a percentage value to the compare function. The compare function is then responsible for mapping the percentage to a reasonable difference between colors (hint: see color metrics).   
3. Trying to load an image again will result in the request being ignored, to avoid duplicates in the storage. This is checked by path.
4. If something doesn't need to be checked, just set the tolerance for it to the maximum value. This way, the comparison will say that every difference found is tolerated, thus not reported.
5. There images selected to be shown and worked upon are called 'active' images in order to avoid confusion with the term 'shown' in its literal sense.
6. All the tabs used in the view extend from a base class which is marked as a view friend. By making them friend, they can access all the elements of the main view object. This include the model (models?) passed initially to the view.

