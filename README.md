# Practice_of_Process-Thread
大学の課題  
プロセスとスレッドの簡単な演習  
* capthread.c  
小文字の文字列を受け取り大文字に変換するcapitalize関数  
この関数を別スレッドとして実行し、親プロセスから文字列を与えることで処理を実行
* capfork.c  
上と同様のことをマルチプロセスで実行  
子プロセスで変換処理、パイプで親プロセスに結果を渡して表示  
* capfork2.c  
親プロセスから子プロセスに小文字の文字列を送り、子プロセスで変換して親プロセスに返し、結果を親プロセスで出力
