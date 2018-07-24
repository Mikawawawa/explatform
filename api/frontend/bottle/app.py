#/usr/bin/env python
#coding=utf-8
from bottle import route, run
from bottle import request
#定义上传路径
path = './upload/'

def getTimestamp():
    import time
    millis = int(round(time.time() * 1000))
    return millis

@route('/upload')
def upload():
    return '''
        <html>
            <head>
            </head>
            <body>
                <form action"/upload" method="post" enctype="multipart/form-data">
                    <input type="file" name="data" />
                    <input type="submit" value="Upload" />
                </form>
            </body>
        </html>
    '''
#文件上传，overwrite=True为覆盖原有的文件，
#如果不加这参数，当服务器已存在同名文件时，将返回“IOError: File exists.”错误
@route('/upload', method = 'POST')
def do_upload():
    upload=request.files.get('data')
    import os.path
    name, ext = os.path.splitext(upload.filename)  #用os.path.splitext方法把文件名和后缀相分离
    upload.filename = str(getTimestamp())+(ext or "."+name)        #修改文件名
    upload.save(path,overwrite=True)  #把文件保存到save_path路径下
    return 'ok'
    
run(host='0.0.0.0', port=8080, debug=True)

