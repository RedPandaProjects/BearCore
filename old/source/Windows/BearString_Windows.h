

 void BearString::ToClipboard(const bchar8 * text)
{
	 ToClipboard(text, GetSize(text));
}

 void BearString::ToClipboard(const bchar16 * text)
{
	 ToClipboard(*BearEncoding::ToANSI(text));
}

 void BearString::ToClipboard(const bchar_utf8 * text)
{
	 ToClipboard(*BearEncoding::ToANSI(text));
}

 void BearCore::BearString::ToClipboard(const bchar8 * text, bsize size)
 {
	 if (OpenClipboard(0))
	 {
		 HGLOBAL hgBuffer;
		 bchar8* chBuffer;
		 EmptyClipboard(); //очищаем буфер
		 hgBuffer = GlobalAlloc(GMEM_DDESHARE, size + 1);//выделяем память
		 chBuffer = (char*)GlobalLock(hgBuffer); //блокируем память
		 CopyWithSizeLimit(chBuffer, size + 1, text, size);
		 GlobalUnlock(hgBuffer);//разблокируем память
		 SetClipboardData(CF_TEXT, hgBuffer);//помещаем текст в буфер обмена
		 CloseClipboard();
	 }
	
 }

  void BearCore::BearString::ToClipboard(const bchar16 * text, bsize size)
 {
	  ToClipboard(*BearEncoding::ToANSI(text), size);
 }

 void BearCore::BearString::ToClipboard(const bchar_utf8 * text, bsize size)
 {
	 ToClipboard(*BearEncoding::ToANSI(text), size);
 }

BearString BearString::GetClipboard()
{
	 BearString result;
	 if (OpenClipboard(0))
	 {
		 HANDLE hData = GetClipboardData(CF_TEXT);//извлекаем текст из буфера обмена
		 bchar8* chBuffer = (bchar8*)GlobalLock(hData);//блокируем память
		 result.assign(*BearEncoding::ToCurrent(chBuffer));
		 GlobalUnlock(hData);//разблокируем память
		 CloseClipboard();//закрываем буфер обмена
	 }
	 return result;
}
