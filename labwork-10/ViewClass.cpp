#include "ViewClass.h"

#include <utility>

void ViewClass::PrintWeatherInformation(const ModelClass* model) {
    std::cout << model->GetCoordinates().name_ << std::endl;
    if (model->GetCoordinates().status_code_ == 200) {
        for (int i = 0; i < model->GetUserDays(); i++) {
            auto document = ftxui::window(
                    ftxui::text(model->GetDay(i).hours_[0].hour_.substr(0, 10)) |
                            ftxui::hcenter | ftxui::flex,
                    ftxui::hbox({VboxDayTime("Morning", model, i, 0) | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 5)
                                         | ftxui::flex, ftxui::separator(),
                                 VboxDayTime("Day", model, i, 1) | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 5)
                                         | ftxui::flex, ftxui::separator(),
                                 VboxDayTime("Evening", model, i, 2) | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 5)
                                         | ftxui::flex, ftxui::separator(),
                                 VboxDayTime("Night", model, i, 3) | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 5)
                                         | ftxui::flex
                                }));
            auto screen =
                    ftxui::Screen::Create(ftxui::Dimension::Full(),       // Width
                                          ftxui::Dimension::Fit(document) // Height
                    );
            Render(screen, document);
            screen.Print();
        }
    } else {
        std::cout << "City not found" << std::endl;
    }
}

ftxui::Element ViewClass::VboxDayTime(std::string day_time,
                                      const ModelClass* model, int day,
                                      int hour) noexcept {
    ftxui::Elements result;
    ftxui::Elements result2;
    result2.push_back(VboxPicture(model->GetDay(day).hours_[hour].weather_code_) |
                      ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 5));
    result.push_back(ftxui::text(std::move(day_time)) | ftxui::hcenter | ftxui::flex |
            ftxui::color(ftxui::Color::Orange1));
    result.push_back(ftxui::separator() | ftxui::flex | ftxui::hcenter);
    result.push_back(
            ftxui::text(
                    std::to_string(model->GetDay(day).hours_[hour].temperature_) + "(" +
                            std::to_string(model->GetDay(day).hours_[hour].apparent_temperature_) +
                            ")" + "°C") |
                    ftxui::flex),
            result.push_back(
                    ftxui::text(
                            "wind speed: " +
                                    std::to_string(model->GetDay(day).hours_[hour].wind_speed_) + "m/s") |
                            ftxui::flex),
            result.push_back(
                    ftxui::text("rainfall: " +
                            std::to_string(
                                    model->GetDay(day).hours_[hour].precipitation_amount_)
                                    .substr(0, 4) + "mm") |
                            ftxui::flex);
    return ftxui::hbox(ftxui::vbox(result2) | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 11), ftxui::separator(),
                       ftxui::vbox(result) | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 11));
}

ftxui::Element ViewClass::VboxPicture(int weather_code) noexcept {
    ftxui::Elements result;
    switch (weather_code) {
        case 0:
            result.push_back(
                    color(ftxui::Color::Orange1, ftxui::text("    \\   /    ")) |
                            ftxui::flex);
            result.push_back(
                    color(ftxui::Color::Orange1, ftxui::text("     .-.     ")) |
                            ftxui::flex);
            result.push_back(
                    color(ftxui::Color::Orange1, ftxui::text("  ― (   ) ―  ")) |
                            ftxui::flex);
            result.push_back(
                    color(ftxui::Color::Orange1, ftxui::text("     `-’     ")) |
                            ftxui::flex);
            result.push_back(
                    color(ftxui::Color::Orange1, ftxui::text("    /   \\    ")) |
                            ftxui::flex);
            break;
        case 1:
            result.push_back(
                    color(ftxui::Color::Yellow, ftxui::text("   \\  /      ")));
            result.push_back(
                    hbox(color(ftxui::Color::Yellow, ftxui::text(" _ /\"\"")),
                         color(ftxui::Color::GrayLight, ftxui::text(".-.    "))));
            result.push_back(
                    hbox(color(ftxui::Color::Yellow, ftxui::text("   \\_")),
                         color(ftxui::Color::GrayLight, ftxui::text("(   ).  "))));
            result.push_back(
                    hbox(color(ftxui::Color::Yellow, ftxui::text("   /")),
                         color(ftxui::Color::GrayLight, ftxui::text("(___(__) "))));
            result.push_back(ftxui::text("             "));
            break;
        case 2:
            result.push_back(
                    color(ftxui::Color::Yellow, ftxui::text("   \\  /      ")));
            result.push_back(
                    hbox(color(ftxui::Color::Yellow, ftxui::text(" _ /\"")),
                         color(ftxui::Color::GrayLight, ftxui::text(".-.     "))));
            result.push_back(
                    hbox(color(ftxui::Color::Yellow, ftxui::text("   \\")),
                         color(ftxui::Color::GrayLight, ftxui::text("(   ).   "))));
            result.push_back(
                    hbox(color(ftxui::Color::Yellow, ftxui::text("   ")),
                         color(ftxui::Color::GrayLight, ftxui::text("(___(__)  "))));
            result.push_back(ftxui::text("             "));
            break;
        case 3:
            result.push_back(ftxui::text("             ") | ftxui::flex |
                    ftxui::hcenter);
            result.push_back(
                    color(ftxui::Color::GrayLight,
                          ftxui::text("       .-.       ") | ftxui::flex | ftxui::hcenter));
            result.push_back(
                    color(ftxui::Color::GrayLight,
                          ftxui::text("      (   ).   ") | ftxui::flex | ftxui::hcenter));
            result.push_back(
                    hbox(color(ftxui::Color::Yellow,
                               ftxui::text("   ") | ftxui::flex | ftxui::hcenter),
                         color(ftxui::Color::GrayLight,
                               ftxui::text(" (___(__)  ") | ftxui::flex | ftxui::hcenter)));
            result.push_back(ftxui::text("             ") | ftxui::flex |
                    ftxui::hcenter);
            break;
        case 45:result.push_back(ftxui::text("             "));
            result.push_back(color(ftxui::Color::White, ftxui::text(" _ - _ - _ - ")));
            result.push_back(color(ftxui::Color::White, ftxui::text(" _ - _ - _ - ")));
            result.push_back(color(ftxui::Color::White, ftxui::text(" _ - _ - _ - ")));
            result.push_back(ftxui::text("             "));
            break;
        case 48:result.push_back(ftxui::text("             "));
            result.push_back(ftxui::text("             "));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text(" _ ")),
                                  color(ftxui::Color::Blue, ftxui::text("*")),
                                  color(ftxui::Color::White, ftxui::text(" _ - _ ")),
                                  color(ftxui::Color::Blue, ftxui::text("* "))));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text(" _ - ")),
                                  color(ftxui::Color::Blue, ftxui::text("*")),
                                  color(ftxui::Color::White, ftxui::text(" - _ - "))));
            break;
        case 51:result.push_back(ftxui::text("             "));
            result.push_back(ftxui::text("             "));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text(" _ ")),
                                  color(ftxui::Color::Blue, ftxui::text("*")),
                                  color(ftxui::Color::White, ftxui::text(" _ - _ ")),
                                  color(ftxui::Color::Blue, ftxui::text("* "))));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text(" _ - ")),
                                  color(ftxui::Color::Blue, ftxui::text("*")),
                                  color(ftxui::Color::White, ftxui::text(" - _ - "))));
            break;
        case 53:result.push_back(ftxui::text("             "));
            result.push_back(ftxui::text("             "));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text(" _ ")),
                                  color(ftxui::Color::Blue, ftxui::text("*")),
                                  color(ftxui::Color::White, ftxui::text(" _ - _ ")),
                                  color(ftxui::Color::Blue, ftxui::text("* "))));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text(" _ - ")),
                                  color(ftxui::Color::Blue, ftxui::text("*")),
                                  color(ftxui::Color::White, ftxui::text(" - _ - "))));
            break;
        case 55:result.push_back(ftxui::text("             "));
            result.push_back(ftxui::text("             "));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text(" _ ")),
                                  color(ftxui::Color::Blue, ftxui::text("*")),
                                  color(ftxui::Color::White, ftxui::text(" _ - _ ")),
                                  color(ftxui::Color::Blue, ftxui::text("* "))));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text(" _ - ")),
                                  color(ftxui::Color::Blue, ftxui::text("*")),
                                  color(ftxui::Color::White, ftxui::text(" - _ - "))));
            break;
        case 56:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(hbox(color(ftxui::Color::Blue, ftxui::text("    ‘ ")),
                                  color(ftxui::Color::Blue, ftxui::text(" ‘ ")))),
                    result.push_back(
                            hbox(color(ftxui::Color::BlueLight, ftxui::text(" ‘ ")),
                                 color(ftxui::Color::BlueLight, ftxui::text(" ‘   "))));
            break;
        case 57:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text("    ‘ ")),
                                  color(ftxui::Color::White, ftxui::text("‘")),
                                  color(ftxui::Color::White, ftxui::text(" ‘ ")),
                                  color(ftxui::Color::White, ftxui::text("‘  "))));
            result.push_back(hbox(color(ftxui::Color::White, ftxui::text("   ‘")),
                                  color(ftxui::Color::White, ftxui::text(" ‘ ")),
                                  color(ftxui::Color::White, ftxui::text("‘")),
                                  color(ftxui::Color::White, ftxui::text(" ‘   "))));
            break;
        case 61:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("    ‘  ‘  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘  ‘   ")));
            break;
        case 63:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("    ‘  ‘  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘   ‘   ")));
            break;
        case 65:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("    ‘ ‘ ‘  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘ ‘  ‘   ")));
            break;
        case 66:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(hbox(color(ftxui::Color::Blue, ftxui::text("    ‘ ")),
                                  color(ftxui::Color::White, ftxui::text("*")),
                                  color(ftxui::Color::Blue, ftxui::text(" ‘ ")))),
                    result.push_back(
                            hbox(color(ftxui::Color::White, ftxui::text("   *")),
                                 color(ftxui::Color::BlueLight, ftxui::text(" ‘ "))));
            break;
        case 67:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(hbox(color(ftxui::Color::Blue, ftxui::text("    ‘ ")),
                                  color(ftxui::Color::White, ftxui::text("*")),
                                  color(ftxui::Color::Blue, ftxui::text(" ‘ ")),
                                  color(ftxui::Color::White, ftxui::text("*  "))));
            result.push_back(
                    hbox(color(ftxui::Color::White, ftxui::text("   *")),
                         color(ftxui::Color::BlueLight, ftxui::text(" ‘ ")),
                         color(ftxui::Color::White, ftxui::text("*")),
                         color(ftxui::Color::BlueLight, ftxui::text(" ‘   "))));
            break;
        case 71:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("    *  *  ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("   *  *   ")));
            break;
        case 73:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("    *  *  ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("   *  *   ")));
            break;
        case 75:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("    * *  *  ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("   *  * *   ")));
            break;
        case 77:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("  ◦ ◦ ◦ ◦   ")));
            result.push_back(color(ftxui::Color::White, ftxui::text(" ◦ ◦ ◦ ◦   ")));
            break;
        case 80:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘ ‘ ‘ ‘  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘ ‘ ‘  ‘   ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘ ‘ ‘  ‘   ")));
            break;
        case 81:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘ ‘ ‘ ‘  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘ ‘ ‘ ‘   ")));
            break;
        case 82:
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::GrayLight, ftxui::text("   (___(__)  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘ ‘ ‘ ‘  ")));
            result.push_back(color(ftxui::Color::Blue, ftxui::text("   ‘ ‘ ‘ ‘   ")));
            break;
        case 85:result.push_back(color(ftxui::Color::GrayLight, ftxui::text("          ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("    *  *  *  ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("   *  *  *   ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("  *  *  *   ")));
            break;
        case 86:result.push_back(color(ftxui::Color::GrayLight, ftxui::text("          ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("    *  *  *  ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("   *  *  *   ")));
            result.push_back(color(ftxui::Color::White, ftxui::text("  *  *  *   ")));
            result.push_back(color(ftxui::Color::White, ftxui::text(" *  *  *   ")));
            break;
        case 95:
            result.push_back(
                    color(ftxui::Color::Palette16::GrayDark, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::Palette16::GrayDark, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::Palette16::GrayDark, ftxui::text("   (___(__)  ")));
            result.push_back(hbox(color(ftxui::Color::Blue, ftxui::text("  ‚‘,")),
                                  color(ftxui::Color::Yellow, ftxui::text("ϟ")),
                                  color(ftxui::Color::Blue, ftxui::text(",‘‚")),
                                  color(ftxui::Color::Yellow, ftxui::text("ϟ"))));
            result.push_back(hbox(color(ftxui::Color::Yellow, ftxui::text(" ϟ")),
                                  color(ftxui::Color::Blue, ftxui::text("‚’‚")),
                                  color(ftxui::Color::Yellow, ftxui::text("ϟ")),
                                  color(ftxui::Color::Blue, ftxui::text(",’, "))));
            break;
        case 96:
            result.push_back(
                    color(ftxui::Color::Palette16::GrayDark, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::Palette16::GrayDark, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::Palette16::GrayDark, ftxui::text("   (___(__)  ")));
            result.push_back(hbox(color(ftxui::Color::Blue, ftxui::text("◦’◦")),
                                  color(ftxui::Color::Yellow, ftxui::text("ϟ")),
                                  color(ftxui::Color::Blue, ftxui::text(",‘‚")),
                                  color(ftxui::Color::Yellow, ftxui::text("ϟ"))));
            result.push_back(hbox(color(ftxui::Color::Yellow, ftxui::text(" ϟ")),
                                  color(ftxui::Color::Blue, ftxui::text("◦’◦")),
                                  color(ftxui::Color::Yellow, ftxui::text("ϟ")),
                                  color(ftxui::Color::Blue, ftxui::text("◦’◦ "))));
            break;
        case 99:
            result.push_back(
                    color(ftxui::Color::Palette16::GrayDark, ftxui::text("     .-.     ")));
            result.push_back(
                    color(ftxui::Color::Palette16::GrayDark, ftxui::text("    (   ).   ")));
            result.push_back(
                    color(ftxui::Color::Palette16::GrayDark, ftxui::text("   (___(__)  ")));
            result.push_back(hbox(color(ftxui::Color::Blue, ftxui::text(" ◦ ◦")),
                                  color(ftxui::Color::Yellow, ftxui::text("ϟ")),
                                  color(ftxui::Color::Blue, ftxui::text("◦ ◦ ◦")))),
                    result.push_back(hbox(color(ftxui::Color::Yellow, ftxui::text(" ϟ")),
                                          color(ftxui::Color::Blue, ftxui::text("◦ ◦ ◦")),
                                          color(ftxui::Color::Yellow, ftxui::text("ϟ")),
                                          color(ftxui::Color::Blue, ftxui::text("◦ ◦ "))));
            break;
    }
    return ftxui::vbox(result) | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 5) |
           ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 15);
}
