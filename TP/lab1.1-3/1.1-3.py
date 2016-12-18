# -*- coding: UTF-8 -*-

import re
import urllib,urllib2
import os
import urlparse


def FindWordInUrl(url, word):
    if not checkedPages.has_key(url):
        checkedPages[url] = 1
        content = urllib2.urlopen(url).read()
        linksList = re.findall('href="(.*?)"', content)
        absoluteLinksList = [urlparse.urljoin(url, k) for k in linksList]
        if word in content:
            print 'Found new page with word'
            checkedPages[url] = 1
            DownloadPage(url)
        for link in absoluteLinksList:
            extension = link.split('.', 1)[-1]
            if '.htm' in extension:
                FindWordInUrl(link, word)

def DownloadPage(url):
    page = urllib2.urlopen(url).read()
    print page
    links = re.findall('src="(.*?)"', page) + re.findall('href="(.*?)"', page)
    convertedFiles = [urlparse.urljoin(url, n) for n in links]
    namePart =  re.findall('<title>(.*?)</title>', page)[0]
    folder = CorrectName(namePart)
    os.mkdir(folder)
    os.chdir(folder)
    for i in range(len(links)):
        url = links[i]
        namePart = url.rsplit('/', 1)[-1]
        fileName = CorrectName(namePart)
        try:
            if '.' in fileName:
                urllib.urlretrieve(convertedFiles[i], fileName)
                print url, folder + '/' + fileName
                page = page.replace(url, folder + '/' + fileName)
        except:
            print 'incorrect url'

    folderParts = os.getcwd().split('\\')[:-1]
    filePath = folderParts[0] + '\\'
    for i in range (1,len(folderParts)):
        filePath += folderParts[i] + '\\'
    os.chdir(filePath)
    f = open(folder + '.html', 'w')
    f.write(page)
    f.close()

def CorrectName(name):
    invalidSymbols = ['/', '|','"','*',':','?', '<', '>','\\' ]
    correctName = ''
    for symbol in name:
        if symbol not in invalidSymbols:
            correctName += symbol
    return correctName


url = "http://lenta.ru"
word = 'Трамп'
checkedPages = {}
FindWordInUrl(url, word)
