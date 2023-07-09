#ifndef LABWORK_7_SUNLYOUS__PARENTFRAME_H_
#define LABWORK_7_SUNLYOUS__PARENTFRAME_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <codecvt>
#include <locale>

#include "Information.h"

class ParentFrame {
protected:
    const int kSizeCoding_ = 1;
    char coding_ = 0;
    std::string text_;
    int size_ = 0;
    std::string frame_name_;
    const int kSizeFrameFlag_ = 2;
    static int CheckSizeInformationHeader(std::ifstream& file);

    void DecodingText(char* buffer, int count);
public:
    virtual void Parse(std::ifstream& file, Information*& info) = 0;

public:
    ParentFrame() = default;
    virtual ~ParentFrame() = default;
};
class TextFrame : public ParentFrame {
public:
    void Parse(std::ifstream& file, Information*& info) override;
    explicit TextFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
};

class XXXFrame : public ParentFrame {
private:
    std::string description_ = "description:";
    char coding_ = 0;

    void Parse(std::ifstream& file, Information*& info) override;

public:
    explicit XXXFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
};

class URLFrame : public ParentFrame {
private:
    void Parse(std::ifstream& file, Information*& info) override;

public:
    explicit URLFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
};

class ETCOFrame : public ParentFrame {
private:
    std::string event_type = "event_type:";
    std::string timestamp = "timestamp:";

    void Parse(std::ifstream& file, Information*& info) override;

public:
    explicit ETCOFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
};

class USLTFrame : public ParentFrame {
private:
    const int kSizeFrameLanguage_ = 3;
    std::string language_ = "language:";
    std::string description_ = "description:";

    void Parse(std::ifstream& file, Information*& info) override;

public:
    explicit USLTFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
};

class SYLTFrame : public ParentFrame {
private:
    const int kSizeFrameLanguage_ = 3;
    std::string language_ = "language:";
    std::string label_format_ = "label format:";
    std::string form_ = "form:";
    std::string type_ = "type:";
    std::string description_ = "description:";
    std::string synchronization_ = "synchronization_";
    std::string timestamp_;

    void Parse(std::ifstream& file, Information*& info) override;

public:
    explicit SYLTFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
};

class COMMFrame : public ParentFrame {
private:
    int kSizeFrameLanguage_ = 3;
    std::string language_ = "language:";
    std::string description_ = "description:";

    void Parse(std::ifstream& file, Information*& info) override;

public:
    explicit COMMFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
};

class RVA2Frame : public ParentFrame {
private:
    std::string identification_ = "identification:";
    std::string type_ = "type:";
    std::string volume_reference_ = "volume reference:";
    std::string bits_ = "bits:";
    std::string volume_ = "volume:";

public:
    explicit RVA2Frame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };

    void Parse(std::ifstream& file, Information*& info) override;
};

class EQU2Frame : public ParentFrame {
private:
    std::string interpolation_method_;
    std::string interpolation_ = "interpolation";
    std::string frequency_ = "frequency";
    std::string volume_control_ = "volume control";
public:
    explicit EQU2Frame(const std::string& frame_name) {
        frame_name_ = frame_name;
    }
    void Parse(std::ifstream& file, Information*& info) override;
};

class PCNTFrame : public ParentFrame {
public:
    explicit PCNTFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
    void Parse(std::ifstream& file, Information*& info) override;
};

class POPMFrame : public ParentFrame {
private:
    std::string rating_ = "rating:";
    std::string counter_ = "counter:";
public:
    explicit POPMFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };

    void Parse(std::ifstream& file, Information*& info) override;
};

class RBUFFrame : public ParentFrame {
private:
    std::string size_buffer_ = "size buffer:";
    std::string flags_ = "flags:";
    std::string size_next_tag_ = "size next tag:";
public:
    explicit RBUFFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
    void Parse(std::ifstream& file, Information*& info) override;
};

class LINKFrame : public ParentFrame {
private:
    std::string indifier_ = "indifier:";
    std::string url_ = "url:";
    std::string frame_id_ = "frame id:";
public:
    explicit LINKFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
    void Parse(std::ifstream& file, Information*& info) override;
};

class POSSFrame : public ParentFrame {
private:
    std::string format_ = "format:";
public:
    explicit POSSFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
    void Parse(std::ifstream& file, Information*& info) override;
};

class USERFrame : public ParentFrame {
private:
    const int kSizeFrameLanguage_ = 3;
    std::string language_ = "language:";
public:
    explicit USERFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
    void Parse(std::ifstream& file, Information*& info) override;
};

class OWNEFrame : public ParentFrame {
private:
    std::string price_ = "price:";
    std::string date_ = "date:";
public:
    explicit OWNEFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
    void Parse(std::ifstream& file, Information*& info) override;
};

class COMRFrame : public ParentFrame {
private:
    std::string price_ = "price:";
    std::string valid_until_ = "valid until:";
    std::string contact_url_ = "contact url:";
    std::string received_as_ = "received as:";
    std::string seller_ = "seller:";
    std::string description_ = "description:";
    std::string picture_type_ = "picture type:";
    std::string logo_mime_type_;
public:
    explicit COMRFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
    void Parse(std::ifstream& file, Information*& info) override;
};

class ENCRFrame : public ParentFrame {
private:
    std::string method_symbol_ = "method_symbol:";
    std::string data_ = "data:";
public:
    explicit ENCRFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
    void Parse(std::ifstream& file, Information*& info) override;
};

class PRIVFrame : public ParentFrame {
private:
    void Parse(std::ifstream& file, Information*& info) override;
    std::string data_ = "data:";
public:
    explicit PRIVFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
};

class SEEKFrame : public ParentFrame {
public:
    std::string size_m;
    explicit SEEKFrame(const std::string& frame_name) {
        frame_name_ = frame_name;
    };
    void Parse(std::ifstream& file, Information*& info) override;
};

#endif //LABWORK_7_SUNLYOUS__PARENTFRAME_H_