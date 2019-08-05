/***********************************************************************************************************************
                                _______           _______  _______  _______  _______
                               (  __   )|\     /|(  __   )(  __   )/ ___   )(  ___  )
                               | (  )  |( \   / )| (  )  || (  )  |\/   )  || (   ) |
                               | | /   | \ (_) / | | /   || | /   |    /   )| (___) |
                               | (/ /) |  ) _ (  | (/ /) || (/ /) |  _/   / |  ___  |
                               |   / | | / ( ) \ |   / | ||   / | | /   _/  | (   ) |
                               |  (__) |( /   \ )|  (__) ||  (__) |(   (__/\| )   ( |
                               (_______)|/     \|(_______)(_______)\_______/|/     \|

   MIT License

   Copyright (c) 2019 Kevin Klein

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
   documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
   Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
   WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
   OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **********************************************************************************************************************/

#include "Telegram.h"

#include "Common.h"
#include "Application.h"
#include "CURLResponseHelper.h"

#include <curl/curl.h>
#include <algorithm>

void
AlmaGrab::Telegram::notify(std::string msg) const
{
  auto token = m_pApp->requireParam(PARAM_TGTOKEN);
  auto chatID = m_pApp->requireParam(PARAM_TGCHATID);
  std::unordered_map<std::string, std::string> params = {
    {"chat_id", chatID},
    {"text", msg}
  };

  CURLResponseHelper rh;
  auto reqURL = "https://api.telegram.org/bot" + token + "/sendMessage" + buildQueryString(params);
  auto curl = (CURL*)m_pApp->getResource(RESOURCE_CURL);
  curl_easy_setopt(curl, CURLOPT_URL, reqURL.c_str());
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, AlmaGrab::CURLResponseHelper::callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rh);

  curl_easy_perform(curl);
}

std::string
AlmaGrab::Telegram::buildQueryString(std::unordered_map<std::string, std::string> values) const
{
  if (values.empty()){
    return "";
  }

  std::string str;
  std::for_each(std::begin(values), std::end(values), [&](auto const& param){
    auto strParam = std::get<0>(param) + '=' + std::get<1>(param);
    str += "&" + strParam;
  });

  // Convert the first '&' into '?'
  str[0] = '?';

  return str;
}
