#include "ParentFrame.h"

void TextFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    file >> coding_;
    char* buffer = new char[size_ - kSizeCoding_];
    file.read(buffer, size_ - kSizeCoding_);
    DecodingText(buffer, size_ - kSizeCoding_);
    info->AddFrame(frame_name_, text_);
    delete[] buffer;
}

void URLFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char* buffer = new char[size_];
    file.read(buffer, size_);
    DecodingText(buffer, size_);
    info->AddFrame(frame_name_, text_);
    delete[] buffer;
}

void XXXFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    file >> coding_;
    char* buffer = new char[size_ - kSizeCoding_];
    file.read(buffer, size_ - kSizeCoding_);
    int count = 0;
    while (buffer[count] != 0) {
        count++;
    }
    char* buf = new char[size_ - kSizeCoding_ - count - 1];
    for (int i = 0; i < size_ - kSizeCoding_ - count - 1; i++) {
        buf[i] = buffer[count + i + 1];
    }
    DecodingText(buffer, count);
    description_ += text_;
    text_.clear();
    DecodingText(buf, size_ - kSizeCoding_ - count - 1);

    info->AddFrame(frame_name_, description_);
    info->AddFrame(frame_name_, text_);
    delete[] buffer;
    delete[] buf;
}

void ETCOFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char* buffer = new char[size_];
    file.read(buffer, size_);
    if (buffer[0] == 1) {
        text_ = "using MPEG [MPEG] frames as unit";
    } else {
        text_ = "using milliseconds as unit";
    }
    if (size_ != 1) {
        event_type = buffer[1];
        for (int i = 2; i < size_; i++) {
            timestamp += buffer[i];
        }
    }
    info->AddFrame(frame_name_, text_);
    info->AddFrame(frame_name_, event_type);
    info->AddFrame(frame_name_, timestamp);
    delete[] buffer;
}

void USLTFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    file >> coding_;
    char* language = new char[kSizeFrameLanguage_];
    file.read(language, kSizeFrameLanguage_);
    for (int i = 0; i < kSizeFrameLanguage_; i++) {
        language_ += language[i];
    }
    info->AddFrame(frame_name_, language_);
    char* buffer = new char[size_ - kSizeCoding_ - kSizeFrameLanguage_];
    file.read(buffer, size_ - kSizeCoding_ - kSizeFrameLanguage_);
    int count = 0;
    while (buffer[count] != 0) {
        count++;
    }
    char* buf = new char[size_ - kSizeCoding_ - count - 1 - kSizeFrameLanguage_];
    for (int i = 0; i < size_ - kSizeCoding_ - kSizeFrameLanguage_ - count - 1; i++) {
        buf[i] = buffer[count + i + 1];
    }
    DecodingText(buffer, count);
    description_ += text_;
    text_.clear();
    DecodingText(buf, size_ - kSizeCoding_ - kSizeFrameLanguage_ - count - 1);
    delete[] buffer;
    delete[] buf;
    delete[] language;
    info->AddFrame(frame_name_, description_);
    info->AddFrame(frame_name_, text_);
}

void SYLTFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    file >> coding_;
    char* language = new char[kSizeFrameLanguage_];
    file.read(language, kSizeFrameLanguage_);
    for (int i = 0; i < kSizeFrameLanguage_; i++) {
        language_ += language[i];
    }
    info->AddFrame(frame_name_, language_);
    char buf;
    file.get(buf);
    label_format_ += buf;
    file.get(buf);
    form_ += buf;
    file.get(buf);
    type_ += buf;
    char* buffer = new char[size_ - kSizeCoding_ - kSizeFrameLanguage_ - 3];
    file.read(buffer, size_ - kSizeCoding_ - kSizeFrameLanguage_ - 3);
    int count = 0;
    for (int i = 0; i < size_ - kSizeFrameLanguage_ - kSizeCoding_ - 3; i++) {
        description_ += buffer[i];
        count++;
        if (buffer[i] == 0) {
            count++;
            break;
        }
    }
    info->AddFrame(frame_name_, description_);
    for (int i = count; i < size_ - kSizeFrameLanguage_ - kSizeCoding_ - 3; i++) {
        synchronization_ += buffer[i];
        count++;
        if (buffer[i] == 0) {
            count++;
            break;
        }
    }
    timestamp_ += buffer[count];
    timestamp_ += buffer[count + 1];
    count += 2;
    for (int i = count; i < size_ - kSizeFrameLanguage_ - kSizeCoding_ - 3; i++) {
        if (buffer[i] == 0) {
            i += timestamp_.length();
        } else {
            text_ += buffer[i];
        }
    }
    info->AddFrame(frame_name_, text_);
    delete[] buffer;
    delete[] language;

}

void COMMFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    file >> coding_;
    char* language = new char[kSizeFrameLanguage_];
    file.read(language, kSizeFrameLanguage_);
    for (int i = 0; i < kSizeFrameLanguage_; i++) {
        language_ += language[i];
    }
    info->AddFrame(frame_name_, language_);
    char* buffer = new char[size_ - kSizeCoding_ - kSizeFrameLanguage_];
    file.read(buffer, size_ - kSizeCoding_ - kSizeFrameLanguage_);
    int count = 0;
    while (buffer[count] != 0) {
        count++;
    }
    char* buf = new char[size_ - kSizeCoding_ - count - 1 - kSizeFrameLanguage_];
    for (int i = 0; i < size_ - kSizeCoding_ - kSizeFrameLanguage_ - count - 1; i++) {
        buf[i] = buffer[count + i + 1];
    }
    DecodingText(buffer, count);
    description_ = text_;
    text_.clear();
    DecodingText(buf, size_ - kSizeCoding_ - kSizeFrameLanguage_ - count - 1);

    info->AddFrame(frame_name_, description_);
    info->AddFrame(frame_name_, text_);
    delete[] language;
    delete[] buffer;
    delete[] buf;
}

void RVA2Frame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char* buffer = new char[size_];
    file.read(buffer, size_);
    int i = 0;
    while (buffer[i] != 0) {
        text_ += buffer[i];
        i++;
    }
    i++;
    type_ += buffer[i + 1];
    volume_reference_ += buffer[i + 2];
    bits_ += buffer[i + 3];
    for (int j = i + 4; j < size_; j++) {
        volume_ += buffer[j];
    }
    info->AddFrame(frame_name_, text_);
    info->AddFrame(frame_name_, type_);
    info->AddFrame(frame_name_, volume_reference_);
    info->AddFrame(frame_name_, bits_);
    info->AddFrame(frame_name_, volume_);
    delete[] buffer;
}

void EQU2Frame::Parse(std::ifstream& file, Information*& info) {
    char byte;
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    file.get(byte);
    interpolation_ += byte;
    char* buffer = new char[size_ - 1];
    file.read(buffer, size_ - 1);
    int i = 0;
    while (buffer[i] != 0) {
        text_ += buffer[i];
        i++;
    }
    i++;
    frequency_ += buffer[i + 1];
    frequency_ += buffer[i + 2];
    volume_control_ += buffer[i + 3];
    volume_control_ += buffer[i + 4];
    info->AddFrame(frame_name_, text_);
    info->AddFrame(frame_name_, interpolation_);
    info->AddFrame(frame_name_, frequency_);
    info->AddFrame(frame_name_, volume_control_);
    delete[] buffer;
}

void PCNTFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char* buffer = new char[size_];
    file.read(buffer, size_);
    for (int i = 0; i < size_; i++) {
        text_ += buffer[i];
    }
    info->AddFrame(frame_name_, text_);
    delete[] buffer;
}

void POPMFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char* buffer = new char[size_];
    file.read(buffer, size_);
    int i = 0;
    text_ += "Email:";
    while (buffer[i] != 0) {
        text_ += buffer[i];
        i++;
    }
    i++;
    rating_ += buffer[i];
    info->AddFrame(frame_name_, text_);
    info->AddFrame(frame_name_, rating_);
    for (int j = i + 1; j < size_; j++) {
        counter_ += buffer[j];
    }
    info->AddFrame(frame_name_, counter_);
    delete[] buffer;
}

void RBUFFrame::Parse(std::ifstream& file, Information*& info) {
    char byte;
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    file.get(byte);
    size_buffer_ += byte;
    file.get(byte);
    size_buffer_ += byte;
    file.get(byte);
    size_buffer_ += byte;
    file.get(byte);
    flags_ += byte;
    char* buffer = new char[size_ - 4];
    file.read(buffer, size_ - 4);
    for (int i = 0; i < size_ - 4; i++) {
        text_ += buffer[i];
    }
    info->AddFrame(frame_name_, size_buffer_);
    info->AddFrame(frame_name_, flags_);
    info->AddFrame(frame_name_, text_);
}

void LINKFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char* ind = new char[4];
    file.read(ind, 4);
    for (int i = 0; i < 4; i++) {
        indifier_ += ind[i];
    }
    char* buffer = new char[size_ - 4];
    file.read(buffer, size_ - 4);
    int i = 0;
    while (buffer[i] != 0) {
        url_ += buffer[i];
        i++;
    }
    i++;
    for (int j = i; j < size_ - 4; j++) {
        text_ += buffer[j];
    }
    info->AddFrame(frame_name_, indifier_);
    info->AddFrame(frame_name_, url_);
    info->AddFrame(frame_name_, text_);
}

void POSSFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char byte;
    file.get(byte);
    format_ += byte;
    char* buffer = new char[size_ - 1];
    file.read(buffer, size_ - 1);
    int i = 0;
    while (buffer[i] != 0) {
        text_ += buffer[i];
        i++;
    }
    i++;
    for (int j = i; j < size_; j++) {
        text_ += buffer[j];
    }
    info->AddFrame(frame_name_, format_);
    info->AddFrame(frame_name_, text_);
    delete[] buffer;
}

void USERFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char byte;
    file.get(byte);
    coding_ = byte;
    char* language = new char[kSizeFrameLanguage_];
    file.read(language, kSizeFrameLanguage_);
    for (int i = 0; i < kSizeFrameLanguage_; i++) {
        language_ += language[i];
    }
    info->AddFrame(frame_name_, language_);
    char* buffer = new char[size_ - 4];
    DecodingText(buffer, size_ - 5);
    info->AddFrame(frame_name_, text_);
    delete[] buffer;
}

void OWNEFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char byte;
    file.get(byte);
    coding_ = byte;
    char* buffer = new char[size_ - 1];
    int i = 0;
    while (buffer[i] != 0) {
        price_ += buffer[i];
        i++;
    }
    i++;
    for (int j = i; j < 8; j++) {
        date_ += buffer[j];
    }
    text_ = "seller:";
    for (int j = i + 8; j < size_ - 1; j++) {
        text_ += buffer[j];
    }
    info->AddFrame(frame_name_, price_);
    info->AddFrame(frame_name_, date_);
    info->AddFrame(frame_name_, text_);
    delete[] buffer;
}

void COMRFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char byte;
    file.get(byte);
    coding_ = byte;
    char* buffer = new char[size_ - 1];
    int i = 0;
    while (buffer[i] != 0) {
        price_ += buffer[i];
        i++;
    }
    i++;
    for (int j = i; j < 8; j++) {
        valid_until_ += buffer[j];
    }
    i += 8;
    while (buffer[i] != 0) {
        contact_url_ += buffer[i];
    }
    i++;
    received_as_ = buffer[i + 1];
    i++;
    while (buffer[i] != 0) {
        seller_ = buffer[i];
    }
    i++;
    while (buffer[i] != 0) {
        description_ += buffer[i];
    }
    i++;
    while (buffer[i] != 0) {
        picture_type_ += buffer[i];
    }
    i++;
    while (i != size_ - 1) {
        logo_mime_type_ += buffer[i];
    }
    info->AddFrame(frame_name_,price_);
    info->AddFrame(frame_name_,valid_until_);
    info->AddFrame(frame_name_,contact_url_);
    info->AddFrame(frame_name_,received_as_);
    info->AddFrame(frame_name_,seller_);
    info->AddFrame(frame_name_,description_);
    info->AddFrame(frame_name_,picture_type_);
    info->AddFrame(frame_name_,logo_mime_type_);
}

void ENCRFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char* buffer = new char [size_];
    int i = 0;
    while (buffer[i] != 0) {
        text_ += buffer[i];
        i++;
    }
    i++;
    method_symbol_ += buffer[i + 1];
    i++;
    for( int j = i; j < size_; j++) {
        data_ += buffer[j];
    }
    info->AddFrame(frame_name_,text_);
    info->AddFrame(frame_name_,method_symbol_);
    info->AddFrame(frame_name_,data_);
}

int ParentFrame::CheckSizeInformationHeader(std::ifstream& file) {
    char buffer[4];
    file.read(buffer, 4);
    int size = 0;
    for (char i : buffer) {
        size <<= 7;
        size |= i & 0x7F;
    }
    return size;
}

void ParentFrame::DecodingText(char* buffer, int count) {
    if (coding_ == 1 || coding_ == 2) {
        for (int i = 2; i < count; i++) {
            text_ += buffer[i];
        }
        std::wstring text_w;
        for (int i = 0; i < text_.size();) {
            int first = text_[i] & 255;
            i++;
            int second = text_[i] & 255;
            i++;
            text_w.push_back(second << 8 | first);
        }
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        text_ = convert.to_bytes(text_w);

    } else {
        for (int i = 0; i < count; i++) {
            text_ += buffer[i];
        }
    }
}

void PRIVFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char* buffer = new char [size_];
    int i = 0;
    while (buffer[i] != 0) {
        text_ += buffer[i];
        i++;
    }
    i++;
    for( int j = i; j < size_; j++) {
        data_ += buffer[j];
    }
    info->AddFrame(frame_name_,text_);
    info->AddFrame(frame_name_,data_);
}
void SEEKFrame::Parse(std::ifstream& file, Information*& info) {
    size_ = CheckSizeInformationHeader(file);
    file.seekg(kSizeFrameFlag_, std::ios::cur);
    char buffer[4];
    file.read(buffer, 4);
    int size = 0;
    for (char i : buffer) {
        size += i - '0';
    }
    size_m += std::to_string(size);
    info->AddFrame(frame_name_, size_m);
}
