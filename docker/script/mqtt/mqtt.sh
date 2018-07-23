cp ../../../api/platform/mqtt/app.js ./
cp ../../../api/platform/mqtt/package.json ./
cp ../../../api/platform/mqtt/package-lock.json ./
docker build -t explatform/mqtt .
rm -rf app.js package.json package-lock.json
