#include "ocr.h"


int TessRecognizePix (Pix *image,
                      const char *lang, std::vector<char *> &outText, const char *datapath,
                      char *error_code, char *error_message) {

  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

  int failed = api->Init(datapath, lang);
  if (failed) {
    pixDestroy(&image);

    const char *code = "ERR_INIT_TESSER";
    const char *message = "Could not initialize tesseract.";
    strcpy(error_code, code);
    strcpy(error_message, message);

    return failed;
  }

  api->SetImage(image);
  pixDestroy(&image);

  outText.insert(outText.end(), "multiple");
  outText.insert(outText.end(), "results");
  tesseract::ResultIterator* iterator = api->GetIterator();
  iterator->Begin();

  do {
    outText.insert(outText.end(), iterator->GetUTF8Text(tesseract::RIL_BLOCK));
  } while(iterator->Next(tesseract::RIL_BLOCK));

  // Get OCR result
  // outText = api->GetUTF8Text();

  // Destroy used object and release memory
  api->End();

  return 0;
}
