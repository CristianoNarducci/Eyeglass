//
// Created by cristiano on 20/07/20.
//

#ifndef EYEGLASS_MODEL_H
#define EYEGLASS_MODEL_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>
#include "AbstractModel.h"
#include "../utils/Observer.h"
#include "../utils/Subject.h"

class Model: public AbstractModel {
protected:
    std::vector<Observer*> observers;
    std::map<wxString,wxImage> imageStorage;

public:
    Model();

    void registerObserver(Observer *observer) override;

    void removeObserver(Observer *observer) override;

    void notify(int eventCode) override;

    void loadImage(wxString path) override;

    void removeImage(wxString path) override;

    void removeAllImages(wxArrayString paths) override;

    const wxImage getImage(wxString path) override;

    const std::map<wxString, wxImage> getAllImages() override;

    double comparePixelAlpha(const char alphaValue1, const char alphaValue2, const double tolerance) override;

    double comparePixelRGB(wxImage::RGBValue RGBValue1, wxImage::RGBValue RGBValue2, const double tolerance) override;

    double comparePixelHSV(wxImage::HSVValue HSVValue1, wxImage::HSVValue HSVValue2, const double tolerance) override;

    void compareAlpha(wxString path1, wxString path2, const double tolerance) override;

    void compareRGB(wxString path1, wxString path2, const double tolerance) override;

    void compareHSV(wxString path1, wxString path2, const double tolerance) override;

    const DiffResult getDifferences(wxString path1, wxString path2) override;

protected:
    void removeCachedDifferences(wxString path1, wxString path2) override;

    void removeAllCachedDifferences() override;
};


#endif //EYEGLASS_MODEL_H
