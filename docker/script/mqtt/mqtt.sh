# 构建应用
cp ../../../api/platform/mqtt/app.js ./
cp ../../../api/platform/mqtt/package.json ./
cp ../../../api/platform/mqtt/package-lock.json ./
docker build -t explatform/mqtt .
rm -rf app.js package.json package-lock.json
# 启动镜像
docker run -d --name mqtt -p 8201:8080 explatform/mqtt