FROM node:18-alpine

WORKDIR /app

COPY package*.json ./

# Устанавливаем зависимости, включая devDependencies
RUN npm install --include=dev

COPY . .

EXPOSE 3000