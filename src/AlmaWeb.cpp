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

#include "AlmaWeb.h"

#include "Common.h"
#include "Notifiable.h"
#include "Application.h"
#include "CURLResponseHelper.h"

#include <curl/curl.h>
#include <regex>
#include <algorithm>

void
AlmaGrab::AlmaWeb::checkForChanges(std::vector<Notifiable*> toNotify) const
{
  auto newVersion = isNewVersion();
  if(newVersion) {
    std::for_each(std::begin(toNotify), std::end(toNotify), [&](auto target){
      target->notify("Attention: Version of AlmaWeb has changed!");
    });
  }
}

bool
AlmaGrab::AlmaWeb::isNewVersion() const
{
  CURLResponseHelper rh;
  auto curl = (CURL*)m_pApp->getResource(RESOURCE_CURL);
  curl_easy_setopt(curl, CURLOPT_URL, "https://almaweb.uni-leipzig.de/");
  curl_easy_setopt(curl, CURLOPT_USERAGENT, USR_AGENT);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, AlmaGrab::CURLResponseHelper::callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rh);

  curl_easy_perform(curl);

  std::regex rgx("customer:[ 	]*[A-Za-z0-9]*\r\n[ 	]*version:[ 	]*([0-9.]*)");
  std::cmatch matches;
  const char* pData = rh.getData();

  if(std::regex_search(pData, pData + rh.getSize(), matches, rgx)) {
    if(std::strcmp(matches[1].str().c_str(), AW_VERSION) == 0){
      return false;
    }
  }

  return true;
}
